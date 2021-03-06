/* file: df_classification_model.cpp */
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
//  Implementation of the class defining the decision forest classification model
//--
*/

#include "algorithms/decision_forest/decision_forest_classification_model.h"
#include "serialization_utils.h"
#include "df_classification_model_impl.h"
#include "collection.h"
#include "dtrees_model_impl_common.h"

using namespace daal::data_management;
using namespace daal::services;
using namespace daal::algorithms::dtrees::internal;

namespace daal
{
namespace algorithms
{
typedef decision_forest::classification::internal::ModelImpl::TreeType::NodeType::Leaf TLeaf;
typedef classifier::TreeNodeVisitor TVisitor;

namespace dtrees
{
namespace internal
{
template<>
void writeLeaf(const TLeaf& l, DecisionTreeNode& row)
{
    row.leftIndexOrClass = l.response.value;
}

template<>
bool visitLeaf(size_t level, const DecisionTreeNode& row, TVisitor& visitor)
{
    return visitor.onLeafNode(level, row.leftIndexOrClass);
}
}
}

namespace decision_forest
{

namespace classification
{
namespace interface1
{
__DAAL_REGISTER_SERIALIZATION_CLASS2(Model, internal::ModelImpl, SERIALIZATION_DECISION_FOREST_CLASSIFICATION_MODEL_ID);
}

namespace internal
{

size_t ModelImpl::numberOfTrees() const
{
    return ImplType::size();
}

void ModelImpl::traverseDF(size_t iTree, classifier::TreeNodeVisitor& visitor) const
{
    if(iTree >= size())
        return;
    const DecisionTreeTable& t = *at(iTree);
    const DecisionTreeNode* aNode = (const DecisionTreeNode*)t.getArray();
    if(aNode)
        traverseNodeDF<TVisitor>(0, 0, aNode, visitor);
}

void ModelImpl::traverseBF(size_t iTree, classifier::TreeNodeVisitor& visitor) const
{
    if(iTree >= size())
        return;
    const DecisionTreeTable& t = *at(iTree);
    const DecisionTreeNode* aNode = (const DecisionTreeNode*)t.getArray();
    NodeIdxArray aCur;//nodes of current layer
    NodeIdxArray aNext;//nodes of next layer
    if(aNode)
    {
        aCur.push_back(0);
        traverseNodesBF<TVisitor>(0, aCur, aNext, aNode, visitor);
    }
}

services::Status ModelImpl::serializeImpl(data_management::InputDataArchive  * arch)
{
    auto s = daal::algorithms::classifier::Model::serialImpl<data_management::InputDataArchive, false>(arch);
    return s.add(ImplType::serialImpl<data_management::InputDataArchive, false>(arch));
}

services::Status ModelImpl::deserializeImpl(const data_management::OutputDataArchive * arch)
{
    auto s = daal::algorithms::classifier::Model::serialImpl<const data_management::OutputDataArchive, true>(arch);
    return s.add(ImplType::serialImpl<const data_management::OutputDataArchive, true>(arch));
}

bool ModelImpl::add(const TreeType& tree)
{
    if(size() >= _serializationData->size())
        return false;
    size_t i = _nTree.inc();
    (*_serializationData)[i - 1].reset(tree.convertToTable());
    return true;
}

} // namespace interface1
} // namespace regression
} // namespace decision_forest
} // namespace algorithms
} // namespace daal
