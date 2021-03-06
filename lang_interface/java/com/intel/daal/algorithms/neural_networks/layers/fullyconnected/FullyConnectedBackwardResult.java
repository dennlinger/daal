/* file: FullyConnectedBackwardResult.java */
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
 * @ingroup fullyconnected_backward
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.fullyconnected;

import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FULLYCONNECTED__FULLYCONNECTEDBACKWARDRESULT"></a>
 * @brief Provides methods to access results obtained with the compute() method of the backward fully-connected layer
 */
public class FullyConnectedBackwardResult extends com.intel.daal.algorithms.neural_networks.layers.BackwardResult {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs the backward fully-connected layer result
     * @param context   Context to manage the backward fully-connected layer result
     */
    public FullyConnectedBackwardResult(DaalContext context) {
        super(context);
        this.cObject = cNewResult();
    }

    public FullyConnectedBackwardResult(DaalContext context, long cObject) {
        super(context, cObject);
    }

    private native long cNewResult();
}
/** @} */
