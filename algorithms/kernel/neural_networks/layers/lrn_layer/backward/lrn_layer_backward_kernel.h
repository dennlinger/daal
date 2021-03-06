/* file: lrn_layer_backward_kernel.h */
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

//++
//  Implementation of the backward local response normalization layer
//--


#ifndef __LRN_LAYER_BACKWARD_KERNEL_H__
#define __LRN_LAYER_BACKWARD_KERNEL_H__

#include "neural_networks/layers/lrn/lrn_layer.h"
#include "neural_networks/layers/lrn/lrn_layer_types.h"
#include "kernel.h"
#include "service_math.h"
#include "numeric_table.h"
#include "service_dnn.h"
#include "service_dnn_internal.h"
#include "layers_threading.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace lrn
{
namespace backward
{
namespace internal
{

/**
 *  \brief Kernel for lrn calculation
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class LRNKernel : public Kernel
{
public:
    services::Status compute(const Tensor &auxDataTensor, const Tensor &sMinusBetaTensor, const Tensor &inputGradientTensor, Tensor &gradientTensor,
        const lrn::Parameter &parameter);

    ~LRNKernel()
    {
        if (lrnPrim)
        {
            dnn::xDelete(lrnPrim);
        }
    }

private:
    typedef daal::internal::Dnn<algorithmFPType, cpu> dnn;

    dnnPrimitive_t lrnPrim = NULL;
};

} // internal
} // backward
} // lrn
} // layers
} // neural_networks
} // algorithms
} // daal

#endif
