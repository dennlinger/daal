/* file: Batch.java */
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
 * @defgroup distributions_uniform_batch Batch
 * @ingroup distributions_uniform
 * @{
 */
/**
 * @brief Contains classes for the uniform distribution
 */
package com.intel.daal.algorithms.distributions.uniform;

import com.intel.daal.algorithms.distributions.Input;
import com.intel.daal.algorithms.distributions.Result;
import com.intel.daal.algorithms.Precision;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__DISTRIBUTIONS__UNIFORM__BATCH"></a>
 * \brief Provides methods for uniform distribution computations in the batch processing mode
 *
 * \par References
 *      - @ref com.intel.daal.algorithms.distributions.Input class
 */
public class Batch extends com.intel.daal.algorithms.distributions.BatchBase {
    public  Parameter    parameter; /*!< Parameters of the uniform distribution */
    public  Method       method;    /*!< Computation method for the distribution */
    private Precision    prec;      /*!< Data type to use in intermediate computations for the distribution */

    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs uniform distribution by copying input objects and parameters of another uniform distribution
     * @param context Context to manage the uniform distribution
     * @param other   A distributions to be used as the source to initialize the input objects
     *                and parameters of this distribution
     */
    public Batch(DaalContext context, Batch other) {
        super(context);
        this.method = other.method;
        prec = other.prec;

        this.cObject = cClone(other.cObject, prec.getValue(), method.getValue());
        input = new Input(context, cGetInput(cObject));
        parameter = new Parameter(context, cInitParameter(cObject, prec.getValue(), method.getValue()));
    }

    /**
     * Constructs the uniform distribution
     * @param context    Context to manage the distribution
     * @param cls        Data type to use in intermediate computations for the distribution, Double.class or Float.class
     * @param method     The distribution computation method, @ref Method
     * @param a          Left bound of the interval
     * @param b          Right bound of the interval
     */
    public Batch(DaalContext context, Class<? extends Number> cls, Method method, double a, double b) {
        super(context);
        constructBatch(context, cls, method, a, b);
    }

    private void constructBatch(DaalContext context, Class<? extends Number> cls, Method method, double a, double b) {
        this.method = method;

        if (method != Method.defaultDense) {
            throw new IllegalArgumentException("method unsupported");
        }
        if (cls != Double.class && cls != Float.class) {
            throw new IllegalArgumentException("type unsupported");
        }

        if (cls == Double.class) {
            prec = Precision.doublePrecision;
        }
        else {
            prec = Precision.singlePrecision;
        }

        this.cObject = cInit(prec.getValue(), method.getValue(), a, b);
        input = new Input(context, cGetInput(cObject));
        parameter = new Parameter(context, cInitParameter(cObject, prec.getValue(), method.getValue()));
        parameter.setA(a);
        parameter.setB(b);
    }

    /**
     * Computes the result of the uniform distribution
     * @return  Uniform distribution result
     */
    @Override
    public Result compute() {
        super.compute();
        return new Result(getContext(), cGetResult(cObject, prec.getValue(), method.getValue()));
    }

    /**
     * Returns the newly allocated uniform distribution
     * with a copy of input objects and parameters of this uniform distribution
     * @param context    Context to manage the distribution
     * @return The newly allocated uniform distribution
     */
    @Override
    public Batch clone(DaalContext context) {
        return new Batch(context, this);
    }

    private native long cInit(int prec, int method, double a, double b);
    private native long cInitParameter(long cAlgorithm, int prec, int method);
    private native long cGetResult(long cAlgorithm, int prec, int method);
    private native long cClone(long algAddr, int prec, int method);
}
/** @} */
