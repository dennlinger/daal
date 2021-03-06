/* file: QRDenseBatch.java */
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

/*
 //  Content:
 //     Java example of computing QR decomposition in the batch processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-QRBATCH">
 * @example QRDenseBatch.java
 */

package com.intel.daal.examples.qr;

import com.intel.daal.algorithms.qr.Batch;
import com.intel.daal.algorithms.qr.InputId;
import com.intel.daal.algorithms.qr.Method;
import com.intel.daal.algorithms.qr.Result;
import com.intel.daal.algorithms.qr.ResultId;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;


class QRDenseBatch {

    /* Input data set parameters */
    private static final String dataset  = "../data/batch/qr.csv";
    private static final int    nVectors = 100;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource dataSource = new FileDataSource(context, dataset,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);

        /* Retrieve the data from an input file */
        dataSource.loadDataBlock();

        NumericTable input = dataSource.getNumericTable();

        /* Create an algorithm to compute QR decomposition */
        Batch qrAlgorithm = new Batch(context, Float.class, Method.defaultDense);
        qrAlgorithm.input.set(InputId.data, input);

        /* Compute QR decomposition */
        Result res = qrAlgorithm.compute();

        NumericTable matrixQ = res.get(ResultId.matrixQ);
        NumericTable matrixR = res.get(ResultId.matrixR);

        /* Print the results */
        Service.printNumericTable("Orthogonal matrix Q:", matrixQ, 10);
        Service.printNumericTable("Triangular matrix R:", matrixR);

        context.dispose();
    }
}
