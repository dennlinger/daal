/* file: engine_batch_impl.h */
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
//  Implementation of the class defining the engine
//--
*/

#ifndef __ENGINE_BATCH_IMPL_H__
#define __ENGINE_BATCH_IMPL_H__

namespace daal
{
namespace algorithms
{
namespace engines
{
namespace internal
{

class BatchBaseImpl
{
public:
    BatchBaseImpl() {}
    virtual void *getState() = 0;
    virtual int getStateSize() const = 0;
    virtual ~BatchBaseImpl() {}
};

} // namespace internal
} // namespace engines
} // namespace algorithms
} // namespace daal

#endif
