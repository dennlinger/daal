/* file: explained_variance_result.cpp */
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

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "daal.h"
#include "pca/quality_metric/JExplainedVarianceResult.h"
#include "pca/quality_metric/JExplainedVarianceResultId.h"
#include "common_helpers.h"

USING_COMMON_NAMESPACES();
using namespace daal::algorithms::pca::quality_metric;
using namespace daal::algorithms::pca::quality_metric::explained_variance;

#define ExplainedVariances com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResultId_explainedVariancesId
#define ExplainedVariancesRatios com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResultId_explainedVariancesRatiosId
#define NoiseVariance com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResultId_noiseVarianceId

/*
* Class:     com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResult
* Method:    cSetResultTable
* Signature: (JIJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_pca_quality_1metric_ExplainedVarianceResult_cSetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id, jlong ntAddr)
{
    jniArgument<explained_variance::Result>::set<explained_variance::ResultId, NumericTable>(resAddr, id, ntAddr);
}

/*
* Class:     com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResult
* Method:    cGetResultTable
* Signature: (JI)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_pca_quality_1metric_ExplainedVarianceResult_cGetResultTable
(JNIEnv *, jobject, jlong resAddr, jint id)
{
    if(id == ExplainedVariances)
        return jniArgument<explained_variance::Result>::get<explained_variance::ResultId, NumericTable>(resAddr, explainedVariances);
    if(id == ExplainedVariancesRatios)
        return jniArgument<explained_variance::Result>::get<explained_variance::ResultId, NumericTable>(resAddr, explainedVariancesRatios);
    if(id == NoiseVariance)
        return jniArgument<explained_variance::Result>::get<explained_variance::ResultId, NumericTable>(resAddr, noiseVariance);
    return (jlong)0;
}

/*
* Class:     com_intel_daal_algorithms_pca_quality_metric_ExplainedVarianceResult
* Method:    cNewResult
* Signature: ()J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_pca_quality_1metric_ExplainedVarianceResult_cNewResult
(JNIEnv *, jobject)
{
    return jniArgument<explained_variance::Result>::newObj();
}
