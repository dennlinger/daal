/* file: kmeans_init_csr_plusplus_distr_step1_fpt_cpu.cpp */
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
//++
//  Implementation of Lloyd method for K-means algorithm
//--
*/

#include "kmeans_init_kernel.h"
#include "kmeans_init_impl.i"
#include "kmeans_init_container.h"

namespace daal
{
namespace algorithms
{
namespace kmeans
{
namespace init
{
namespace interface1
{
template class DistributedContainer<step1Local, DAAL_FPTYPE, plusPlusCSR, DAAL_CPU>;
}
namespace internal
{
template class KMeansinitStep1LocalKernel<plusPlusCSR, DAAL_FPTYPE, DAAL_CPU>;
} // namespace daal::algorithms::kmeans::init::internal
} // namespace daal::algorithms::kmeans::init
} // namespace daal::algorithms::kmeans
} // namespace daal::algorithms
} // namespace daal
