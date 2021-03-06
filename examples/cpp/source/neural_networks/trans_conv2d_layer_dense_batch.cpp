/* file: trans_conv2d_layer_dense_batch.cpp */
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
!  Content:
!    C++ example of forward and backward two-dimensional transposed convolution layer usage
!
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-TRANSPOSEDCONVOLUTION2D_LAYER_BATCH"></a>
 * \example trans_conv2d_layer_dense_batch.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms;
using namespace daal::algorithms::neural_networks::layers;
using namespace daal::data_management;
using namespace daal::services;

/* Input data set name */
string datasetFileName = "../data/batch/layer.csv";

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 1, &datasetFileName);

    /* Create collection of dimension sizes of the input data tensor */
    Collection<size_t> inDims;
    inDims.push_back(1);
    inDims.push_back(2);
    inDims.push_back(4);
    inDims.push_back(4);
    TensorPtr tensorData = TensorPtr(new HomogenTensor<>(inDims, Tensor::doAllocate, 1.0f));

    /* Create an algorithm to compute forward two-dimensional transposed convolution layer results using default method */
    transposed_conv2d::forward::Batch<> transposedConv2dLayerForward;
    transposedConv2dLayerForward.input.set(forward::data, tensorData);


    /* Compute forward two-dimensional transposed convolution layer results */
    transposedConv2dLayerForward.compute();

    /* Get the computed forward two-dimensional transposed convolution layer results */
    transposed_conv2d::forward::ResultPtr forwardResult = transposedConv2dLayerForward.getResult();
    printTensor(forwardResult->get(forward::value), "Two-dimensional transposed convolution layer result (first 5 rows):", 5, 15);
    printTensor(forwardResult->get(transposed_conv2d::auxWeights), "Two-dimensional transposed convolution layer weights (first 5 rows):", 5, 15);


    const Collection<size_t> &gDims = forwardResult->get(forward::value)->getDimensions();
    /* Create input gradient tensor for backward two-dimensional transposed convolution layer */
    TensorPtr tensorDataBack = TensorPtr(new HomogenTensor<>(gDims, Tensor::doAllocate, 0.01f));

    /* Create an algorithm to compute backward two-dimensional transposed convolution layer results using default method */
    transposed_conv2d::backward::Batch<> transposedConv2dLayerBackward;
    transposedConv2dLayerBackward.input.set(backward::inputGradient, tensorDataBack);
    transposedConv2dLayerBackward.input.set(backward::inputFromForward, forwardResult->get(forward::resultForBackward));


    /* Compute backward two-dimensional transposed convolution layer results */
    transposedConv2dLayerBackward.compute();

    /* Get the computed backward two-dimensional transposed convolution layer results */
    backward::ResultPtr backwardResult = transposedConv2dLayerBackward.getResult();
    printTensor(backwardResult->get(backward::gradient),
                "Two-dimensional transposed convolution layer backpropagation gradient result (first 5 rows):", 5, 15);
    printTensor(backwardResult->get(backward::weightDerivatives),
                "Two-dimensional transposed convolution layer backpropagation weightDerivative result (first 5 rows):", 5, 15);
    printTensor(backwardResult->get(backward::biasDerivatives),
                "Two-dimensional transposed convolution layer backpropagation biasDerivative result (first 5 rows):", 5, 15);

    return 0;
}
