/* file: Convolution2dPadding.java */
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
 * @ingroup convolution2d
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.convolution2d;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__CONVOLUTION2D__CONVOLUTION2DPADDING"></a>
 * \brief Data structure representing the number of data to be implicitly added to the subtensor
 */
public final class Convolution2dPadding {
    private long[] size;     /*!< Array of numbers of data to be implicitly added to the subtensor */

    /**
    * Constructs Convolution2dPadding with parameters
    * @param first  The first number of data to be implicitly added to the subtensor
    * @param second The second number of data to be implicitly added to the subtensor
    */
    public Convolution2dPadding(long first, long second) {
        size = new long[2];
        size[0] = first;
        size[1] = second;
    }

    /**
     *  Sets the array of numbers of data to be implicitly added to the subtensor
    * @param first  The first number of data to be implicitly added to the subtensor
    * @param second The second number of data to be implicitly added to the subtensor
     */
    public void setSize(long first, long second) {
        size[0] = first;
        size[1] = second;
    }

    /**
    *  Gets the array of numbers of data to be implicitly added to the subtensor
    * @return Array of numbers of data to be implicitly added to the subtensor
    */
    public long[] getSize() {
        return size;
    }
}
/** @} */
