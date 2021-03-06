/* file: SparkRidgeRegressionNormEq.java */
/*******************************************************************************
* Copyright 2017-2018 Intel Corporation.
*
* This software and the related documents are Intel copyrighted  materials,  and
* your use of  them is  governed by the  express license  under which  they were
* provided to you (License).  Unless the License provides otherwise, you may not
* use, modify, copy, publish, distribute,  disclose or transmit this software or
* the related documents without Intel's prior written permission.
*
* This software and the related documents  are provided as  is,  with no express
* or implied  warranties,  other  than those  that are  expressly stated  in the
* License.
*
* License:
* http://software.intel.com/en-us/articles/intel-sample-source-code-license-agr
* eement/
*******************************************************************************/

/*
//  Content:
//      Java sample of ridge regression in the distributed processing mode.
//
//      The program trains the ridge regression model on a training
//      data set with the normal equations method and computes regression for
//      the test data.
////////////////////////////////////////////////////////////////////////////////
*/

package DAAL;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;

import org.apache.spark.api.java.*;
import org.apache.spark.api.java.function.*;
import org.apache.spark.SparkConf;

import com.intel.daal.algorithms.ridge_regression.*;
import com.intel.daal.algorithms.ridge_regression.training.*;
import com.intel.daal.algorithms.ridge_regression.prediction.*;

import scala.Tuple2;
import com.intel.daal.data_management.data.*;
import com.intel.daal.services.*;

public class SparkRidgeRegressionNormEq {
    /* Class containing the algorithm results */
    static class RidgeRegressionResult {
        public HomogenNumericTable prediction;
        public HomogenNumericTable beta;
    }

    public static RidgeRegressionResult runRidgeRegression(
            DaalContext context,
            JavaRDD<Tuple2<HomogenNumericTable, HomogenNumericTable>> trainDataRDD,
            JavaRDD<Tuple2<HomogenNumericTable, HomogenNumericTable>> testDataRDD) {

        JavaRDD<PartialResult> partsRDD = trainLocal(trainDataRDD);

        Model model = trainMaster(context, partsRDD);

        HomogenNumericTable prediction = testModel(context, model, testDataRDD);

        RidgeRegressionResult result = new RidgeRegressionResult();
        result.beta = (HomogenNumericTable)model.getBeta();
        result.prediction = prediction;
        return result;
    }

    private static JavaRDD<PartialResult> trainLocal(
            JavaRDD<Tuple2<HomogenNumericTable, HomogenNumericTable>> trainDataRDD) {

        return trainDataRDD.map(new Function<Tuple2<HomogenNumericTable, HomogenNumericTable>, PartialResult>() {
            public PartialResult call(Tuple2<HomogenNumericTable, HomogenNumericTable> tup) {
                DaalContext context = new DaalContext();

                /* Create an algorithm object to train the ridge regression model with the normal equations method */
                TrainingDistributedStep1Local ridgeRegressionTraining = new TrainingDistributedStep1Local(
                    context, Double.class, TrainingMethod.normEqDense);

                /* Set the input data on local nodes */
                tup._1.unpack(context);
                tup._2.unpack(context);
                ridgeRegressionTraining.input.set(TrainingInputId.data, tup._1);
                ridgeRegressionTraining.input.set(TrainingInputId.dependentVariable, tup._2);

                /* Build a partial ridge regression model */
                PartialResult pres = ridgeRegressionTraining.compute();
                pres.pack();

                context.dispose();
                return pres;
            }
        });
    }

    private static Model trainMaster(DaalContext context, JavaRDD<PartialResult> partsRDD) {

        /* Create an algorithm object to train the ridge regression model with the normal equations method */
        TrainingDistributedStep2Master ridgeRegressionTraining = new TrainingDistributedStep2Master(
            context, Double.class, TrainingMethod.normEqDense);

        /* Add partial results computed on local nodes to the algorithm on the master node */
        List<PartialResult> collectedPres = partsRDD.collect();
        for (PartialResult value : collectedPres) {
            value.unpack(context);
            ridgeRegressionTraining.input.add(MasterInputId.partialModels, value);
        }

        /* Build and retrieve the final ridge regression model */
        ridgeRegressionTraining.compute();

        TrainingResult trainingResult = ridgeRegressionTraining.finalizeCompute();

        Model model = trainingResult.get(TrainingResultId.model);
        return model;
    }

    private static HomogenNumericTable testModel(
            DaalContext context,
            final Model model,
            JavaRDD<Tuple2<HomogenNumericTable, HomogenNumericTable>> testData) {

        /* Create algorithm objects to predict values of ridge regression with the default method */
        PredictionBatch ridgeRegressionPredict = new PredictionBatch(
            context, Double.class, PredictionMethod.defaultDense);

        /* Pass the test data to the algorithm */
        List<Tuple2<HomogenNumericTable, HomogenNumericTable>> parts_List = testData.collect();
        for (Tuple2<HomogenNumericTable, HomogenNumericTable> value : parts_List) {
            value._1.unpack(context);
            ridgeRegressionPredict.input.set(PredictionInputId.data, value._1);
        }

        ridgeRegressionPredict.input.set(PredictionInputId.model, model);

        /* Compute and retrieve the prediction results */
        PredictionResult predictionResult = ridgeRegressionPredict.compute();

        return (HomogenNumericTable)predictionResult.get(PredictionResultId.prediction);
    }
}
