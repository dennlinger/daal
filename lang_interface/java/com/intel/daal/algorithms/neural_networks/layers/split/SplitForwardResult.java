/* file: SplitForwardResult.java */
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
 * @ingroup split_forward
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.split;

import com.intel.daal.data_management.data.Factory;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.data_management.data.KeyValueDataCollection;
import com.intel.daal.data_management.data.Factory;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SPLIT__SPLITFORWARDRESULT"></a>
 * @brief Class that provides methods to access the result obtained with the compute() method of the forward split layer
 */
public final class SplitForwardResult extends com.intel.daal.algorithms.neural_networks.layers.ForwardResult {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs the forward split layer result
     * @param context   Context to manage the forward split layer result
     */
    public SplitForwardResult(DaalContext context) {
        super(context);
        this.cObject = cNewResult();
    }

    public SplitForwardResult(DaalContext context, long cObject) {
        super(context, cObject);
    }

    /**
     * Returns the result of the forward split layer
     * @param  id   Identifier of the result
     * @return Result that corresponds to the given identifier
     */
    public KeyValueDataCollection get(SplitForwardResultLayerDataId id) {
        if (id == SplitForwardResultLayerDataId.valueCollection) {
            return (KeyValueDataCollection)Factory.instance().createObject(getContext(), cGetValue(cObject, id.getValue()));
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    /**
     * Returns the result of the forward split layer
     * @param  id     Identifier of the result
     * @param  index  SplitIndex of the tensor to be returned
     * @return Result that corresponds to the given identifier
     */
    public Tensor get(SplitForwardResultLayerDataId id, long index) {
        if (id == SplitForwardResultLayerDataId.valueCollection) {
            return (Tensor)Factory.instance().createObject(getContext(), cGetValue(cObject, id.getValue(), index));
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    /**
     * Sets the result of the forward split layer
     * @param id    Identifier of the result
     * @param val   Result that corresponds to the given identifier
     * @param index SplitIndex of the tensor to be set
     */
    public void set(SplitForwardResultLayerDataId id, Tensor val, long index) {
        if (id == SplitForwardResultLayerDataId.valueCollection) {
            cSetValue(cObject, id.getValue(), val.getCObject(), index);
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    private native long cNewResult();

    private native long cGetValue(long cObject, int id);
    private native long cGetValue(long cObject, int id, long index);
    private native void cSetValue(long cObject, int id, long ntAddr, long index);
}
/** @} */
