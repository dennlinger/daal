/* file: ridge_regression_training_distributed_input.cpp */
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
//  Implementation of ridge regression algorithm classes.
//--
*/

#include "algorithms/ridge_regression/ridge_regression_training_types.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace ridge_regression
{
namespace training
{
namespace interface1
{

DistributedInput<step2Master>::DistributedInput() : daal::algorithms::Input(lastStep2MasterInputId + 1)
{
    Argument::set(partialModels, DataCollectionPtr(new DataCollection()));
};

DistributedInput<step2Master>::DistributedInput(const DistributedInput<step2Master>& other) : daal::algorithms::Input(other){}

/**
 * Gets an input object for ridge regression model-based training in the second step of the distributed processing mode
 * \param[in] id    Identifier of the input object
 * \return          %Input object that corresponds to the given identifier
 */
DataCollectionPtr DistributedInput<step2Master>::get(Step2MasterInputId id) const
{
    return staticPointerCast<DataCollection, SerializationIface>(Argument::get(id));
}
/**
 * Sets an input object for ridge regression model-based training in the second step of the distributed processing mode
 * \param[in] id    Identifier of the input object
 * \param[in] ptr   %Input object
 */
void DistributedInput<step2Master>::set(Step2MasterInputId id, const DataCollectionPtr & ptr)
{
    Argument::set(id, ptr);
}
/**
 Adds an input object for ridge regression model-based training in the second step of the distributed processing mode
 * \param[in] id      Identifier of the input object
 * \param[in] partialResult   %Input object
 */
void DistributedInput<step2Master>::add(Step2MasterInputId id, const PartialResultPtr & partialResult)
{
    const DataCollectionPtr collection = staticPointerCast<DataCollection, SerializationIface>(Argument::get(id));
    collection->push_back(staticPointerCast<SerializationIface, ridge_regression::Model>(partialResult->get(training::partialModel)));
}
/**
 * Returns the number of columns in the input data set
 * \return Number of columns in the input data set
 */
size_t DistributedInput<step2Master>::getNumberOfFeatures() const
{
    const DataCollectionPtr partialModelsCollection = static_cast<DataCollectionPtr >(get(partialModels));
    if (partialModelsCollection->size() == 0) { return 0; }
    const ridge_regression::Model * const partialModel = static_cast<const daal::algorithms::ridge_regression::Model *>(((*partialModelsCollection)[0]).get());
    return partialModel->getNumberOfFeatures();
}
/**
 * Returns the number of dependent variables
 * \return Number of dependent variables
 */
size_t DistributedInput<step2Master>::getNumberOfDependentVariables() const
{
    const DataCollectionPtr partialModelsCollection = static_cast<DataCollectionPtr >(get(partialModels));
    if (partialModelsCollection->size() == 0) { return 0; }
    const ridge_regression::Model * const partialModel = static_cast<const daal::algorithms::ridge_regression::Model *>(((*partialModelsCollection)[0]).get());
    return partialModel->getNumberOfResponses();
}
/**
 * Checks an input object for ridge regression model-based training in the second step
 * of the distributed processing mode
 */
services::Status DistributedInput<step2Master>::check(const daal::algorithms::Parameter *parameter, int method) const
{
    DataCollectionPtr collection = DataCollection::cast(Argument::get(partialModels));
    DAAL_CHECK(collection, ErrorNullInputDataCollection);

    size_t nBlocks = collection->size();
    DAAL_CHECK(nBlocks > 0, ErrorIncorrectNumberOfInputNumericTables);

    DAAL_CHECK((*collection)[0], ErrorNullModel);
    ridge_regression::ModelPtr firstPartialModel = ridge_regression::Model::cast((*collection)[0]);
    DAAL_CHECK(firstPartialModel, ErrorIncorrectElementInPartialResultCollection);

    size_t nBeta = firstPartialModel->getNumberOfBetas();
    size_t nResponses = firstPartialModel->getNumberOfResponses();

    services::Status s;

    for(size_t i = 0; i < nBlocks; i++)
    {
        DAAL_CHECK((*collection)[i], ErrorNullModel);
        ridge_regression::ModelPtr partialModel = ridge_regression::Model::cast((*collection)[i]);

        DAAL_CHECK(partialModel, ErrorIncorrectElementInPartialResultCollection);

        DAAL_CHECK_STATUS(
            s, ridge_regression::checkModel(partialModel.get(), *parameter, nBeta, nResponses, method));
    }

    return s;
}

} // namespace interface1
} // namespace training
} // namespace ridge_regression
} // namespace algorithms
} // namespace daal
