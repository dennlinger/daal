/* file: InitBatch.java */
/*******************************************************************************
* Copyright 2014-2018 Intel Corporation.
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
*******************************************************************************/

/**
 * @defgroup kmeans K-means Clustering
 * @brief Contains classes for the K-Means algorithm
 * @ingroup analysis
 * @defgroup kmeans_init Initialization
 * @brief Contains classes for computing initial clusters for the K-Means algorithm
 * @ingroup kmeans
 * @{
 */
/**
 * @defgroup kmeans_init_batch Batch
 * @ingroup kmeans_init
 * @{
 */
/**
 * @brief Contains classes for computing initial clusters for the K-Means algorithm in the batch processing mode
 */
package com.intel.daal.algorithms.kmeans.init;

import com.intel.daal.algorithms.AnalysisBatch;
import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.Precision;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__KMEANS__INIT__INITBATCH"></a>
 * @brief Computes initial clusters for the K-Means algorithm in the batch processing mode
 * <!-- \n<a href="DAAL-REF-KMEANS-ALGORITHM">K-Means algorithm initialization description and usage models</a> -->
 *
 * @par References
 *      - @ref InitInputId class
 *      - @ref ResultId class
 *      - @ref Input class
 */
public class InitBatch extends AnalysisBatch {
    public InitInput     input;     /*!< %Input data */
    public InitParameter parameter; /*!< Parameters for computing initial clusters */
    public InitMethod    method;    /*!< %Method for computing initial clusters */
    private Precision    precision; /*!< Data type for computing initial clusters to use in intermediate computations */

    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs an algorithm for computing initial clusters for the K-Means algorithm in the batch processing mode
     * by copying input objects and parameters of another algorithm
     * @param context     Context to manage initial clusters for the K-Means algorithm
     * @param other       An algorithm to be used as the source to initialize the input objects
     *                    and parameters of the algorithm
     */
    public InitBatch(DaalContext context, InitBatch other) {
        super(context);
        this.method = other.method;
        precision = other.precision;

        this.cObject = cClone(other.cObject, precision.getValue(), this.method.getValue());
        input = new InitInput(getContext(), cGetInput(cObject, precision.getValue(), method.getValue()));
        parameter = new InitParameter(getContext(), cInitParameter(cObject, precision.getValue(), method.getValue()), 0, 0);
    }

    /**
     * Constructs an algorithm for computing initial clusters for the K-Means algorithm in the batch processing mode
     * @param context     Context to manage initial clusters for the K-Means algorithm
     * @param cls         Data type to use in intermediate computations of initial clusters for the K-Means algorithm,
     *                    Double.class or Float.class
     * @param method      %Method of computing initial clusters for the algorithm, @ref InitMethod
     * @param nClusters   Number of initial clusters for the K-Means algorithm
     */
    public InitBatch(DaalContext context, Class<? extends Number> cls, InitMethod method, long nClusters) {
        super(context);
        this.method = method;
        if (cls != Double.class && cls != Float.class) {
            throw new IllegalArgumentException("type unsupported");
        }

        if (this.method != InitMethod.defaultDense     && this.method != InitMethod.randomDense &&
            this.method != InitMethod.plusPlusDense    && this.method != InitMethod.parallelPlusDense &&
            this.method != InitMethod.deterministicCSR && this.method != InitMethod.randomCSR &&
            this.method != InitMethod.plusPlusCSR      && this.method != InitMethod.parallelPlusCSR &&
            this.method != InitMethod.deterministicDense) {
            throw new IllegalArgumentException("method unsupported");
        }

        if (cls == Double.class) {
            precision = Precision.doublePrecision;
        } else {
            precision = Precision.singlePrecision;
        }

        this.cObject = cInit(precision.getValue(), this.method.getValue(), nClusters);

        input = new InitInput(getContext(), cGetInput(cObject, precision.getValue(), method.getValue()));
        parameter = new InitParameter(getContext(), cInitParameter(cObject, precision.getValue(), method.getValue()), 0, 0);
    }

    /**
     * Computes initial clusters for the K-Means algorithm
     * @return  Results of computing initial clusters for the K-Means algorithm
    */
    @Override
    public InitResult compute() {
        super.compute();
        InitResult result = new InitResult(getContext(), cGetResult(cObject, precision.getValue(), method.getValue()));
        return result;
    }

    /**
     * Registers user-allocated memory to store the results of computing initial clusters for the K-Means algorithm
     * @param result    Structure to store the results of computing initial clusters for the K-Means algorithm */
    public void setResult(InitResult result) {
        cSetResult(cObject, precision.getValue(), method.getValue(), result.getCObject());
    }

    /**
     * Returns the newly allocated algorithm for computing initial clusters for the K-Means algorithm
     * in the batch processing mode with a copy of input objects and parameters of this algorithm
     * @param context     Context to manage initial clusters for the K-Means algorithm
     *
     * @return The newly allocated algorithm
     */
    @Override
    public InitBatch clone(DaalContext context) {
        return new InitBatch(context, this);
    }

    private native long cInit(int precision, int method, long nClusters);

    private native void cSetResult(long cAlgorithm, int prec, int method, long cObject);

    private native long cGetResult(long cAlgorithm, int prec, int method);

    private native long cInitParameter(long algAddr, int prec, int method);

    private native long cGetInput(long cAlgorithm, int prec, int method);

    private native long cClone(long algAddr, int prec, int method);
}
/** @} */
/** @} */
/** @} */
