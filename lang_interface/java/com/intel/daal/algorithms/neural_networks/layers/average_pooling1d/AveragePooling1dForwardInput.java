/* file: AveragePooling1dForwardInput.java */
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
 * @defgroup average_pooling1d_forward Forward One-dimensional Average Pooling Layer
 * @brief Contains classes for forward average 1D pooling layer
 * @ingroup average_pooling1d
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.average_pooling1d;

import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING1D__AVERAGEPOOLING1DFORWARDINPUT"></a>
 * @brief %Input object for the forward one-dimensional average pooling layer
 */
public class AveragePooling1dForwardInput extends com.intel.daal.algorithms.neural_networks.layers.pooling1d.Pooling1dForwardInput {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public AveragePooling1dForwardInput(DaalContext context, long cObject) {
        super(context, cObject);
    }
}
/** @} */
