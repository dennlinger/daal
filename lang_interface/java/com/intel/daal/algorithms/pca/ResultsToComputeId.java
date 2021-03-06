/* file: ResultsToComputeId.java */
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
 * @ingroup pca
 * @{
 */
package com.intel.daal.algorithms.pca;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__RESULTTOCOMPUTEID"></a>
 * \brief Available identifiers of results of the PCA algorithm
 */
public final class ResultsToComputeId {

    public static final long none     = 0x0000000000000000L; /*!< No optional result */
    public static final long mean     = 0x0000000000000001L; /*!< Compute mean */
    public static final long variance = 0x0000000000000002L; /*!< Compute variance */
    public static final long eigenvalue = 0x0000000000000004L; /*!< Compute variance */
}/** @} */
