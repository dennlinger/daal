/* file: spatial_stochastic_pooling2d_forward_result.cpp */
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

#include <jni.h>
#include "neural_networks/layers/spatial_stochastic_pooling2d/JSpatialStochasticPooling2dForwardResult.h"
#include "neural_networks/layers/spatial_stochastic_pooling2d/JSpatialStochasticPooling2dLayerDataId.h"
#include "neural_networks/layers/spatial_stochastic_pooling2d/JSpatialStochasticPooling2dLayerDataNumericTableId.h"

#include "daal.h"

#include "common_helpers.h"

#define auxSelectedIndicesId com_intel_daal_algorithms_neural_networks_layers_spatial_stochastic_pooling2d_SpatialStochasticPooling2dLayerDataId_auxSelectedIndicesId
#define auxInputDimensionsId com_intel_daal_algorithms_neural_networks_layers_spatial_stochastic_pooling2d_SpatialStochasticPooling2dLayerDataNumericTableId_auxInputDimensionsId

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::neural_networks::layers::spatial_stochastic_pooling2d;

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult
 * Method:    cNewResult
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_spatial_1stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult_cNewResult
(JNIEnv *env, jobject thisObj)
{
    return jniArgument<forward::Result>::newObj();
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult
 * Method:    cGetValue
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_spatial_1stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult_cGetValue
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id)
{
    if (id == auxSelectedIndicesId)
    {
        return jniArgument<forward::Result>::get<LayerDataId, Tensor>(resAddr, id);
    }

    return (jlong)0;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult
 * Method:    cSetValue
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_spatial_1stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult_cSetValue
(JNIEnv *env, jobject thisObj, jlong resAddr, jint id, jlong ntAddr)
{
    if (id == auxSelectedIndicesId)
    {
        jniArgument<forward::Result>::set<LayerDataId, Tensor>(resAddr, auxSelectedIndices, id);
    }
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_spatial_stochastic_pooling2d_SpatialStochasticPooling2dForwardResult
 * Method:    cGetNumericTableValue
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_spatial_1stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult_cGetNumericTableValue
  (JNIEnv *env, jobject thisObj, jlong resAddr, jint id)
{
    if (id == auxInputDimensionsId)
    {
        return jniArgument<forward::Result>::get<LayerDataNumericTableId, NumericTable>(resAddr, id);
    }

    return (jlong)0;
}

/*
 * Class:     com_intel_daal_algorithms_neural_networks_layers_spatial_stochastic_pooling2d_SpatialStochasticPooling2dForwardResult
 * Method:    cSetNumericTableValue
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_neural_1networks_layers_spatial_1stochastic_1pooling2d_SpatialStochasticPooling2dForwardResult_cSetNumericTableValue
  (JNIEnv *env, jobject thisObj, jlong resAddr, jint id, jlong ntAddr)
{
    if (id == auxInputDimensionsId)
    {
        jniArgument<forward::Result>::set<LayerDataNumericTableId, NumericTable>(resAddr, auxInputDimensions, id);
    }
}
