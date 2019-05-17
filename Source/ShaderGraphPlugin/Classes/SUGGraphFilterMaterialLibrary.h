////////////////////////////////////////////////////////////////////////////////
//
// MIT License
// 
// Copyright (c) 2018-2019 Nuraga Wiswakarma
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////
// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SUGGraphTypes.h"
#include "SUGGraphFilterMaterialLibrary.generated.h"

class UMaterialInterface;
class USUGGraphTask;
class USUGGraphTask_ApplyMaterial;
class USUGGraphTask_BlurFilter1D;
class USUGGraphTask_ErodeFilter;

UCLASS()
class SHADERGRAPHPLUGIN_API USUGGraphFilterMaterialLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

    typedef FSUGGraphParameterNameMap FParamNameMap;
    typedef FRULShaderScalarParameter FScalarParam;
    typedef FRULShaderVectorParameter FVectorParam;
    typedef FSUGGraphTextureParameter FTextureParam;

public:

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Distance Filter", AutoCreateRefTerm="TaskConfig,MaterialRef,ScalarParameters,VectorParameters,TextureParameters", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask,ScalarParameters,VectorParameters,TextureParameters,ParameterCategoryName"))
    static USUGGraphTask_ApplyMaterial* AddDistanceFilterTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters,
        FName ParameterCategoryName,
        FSUGGraphTextureInput SourceTexture,
        float DistanceSteps = 1.f
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Noise", AutoCreateRefTerm="TaskConfig,MaterialRef,ScalarParameters,VectorParameters,TextureParameters", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask,ScalarParameters,VectorParameters,TextureParameters,ParameterCategoryName"))
    static USUGGraphTask_ApplyMaterial* AddDrawNoiseTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters,
        FName ParameterCategoryName,
        FSUGGraphTextureInput SourceTexture,
        FSUGGraphTextureInput MaskTexture,
        FLinearColor ValueRemapRange = FLinearColor(0.f,1.f,0.f,1.f),
        FLinearColor MaskRemapRange = FLinearColor(0.f,1.f,0.f,1.f),
        FVector Offset = FVector::ZeroVector,
        float Scale = 1.f
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Blur Filter 1D", AutoCreateRefTerm="TaskConfig,MaterialRef,ScalarParameters,VectorParameters,TextureParameters", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask,ScalarParameters,VectorParameters,TextureParameters,ParameterCategoryName"))
    static USUGGraphTask_BlurFilter1D* AddBlurFilter1DTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_BlurFilter1D> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters,
        FName ParameterCategoryName,
        FSUGGraphTextureInput SourceTexture,
        float BlurSampleCount = 1.f
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Erode Filter", AutoCreateRefTerm="TaskConfig,MaterialRef,ScalarParameters,VectorParameters,TextureParameters", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask,ScalarParameters,VectorParameters,TextureParameters,ParameterCategoryName"))
    static USUGGraphTask_ErodeFilter* AddErodeFilterTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_ErodeFilter> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters,
        FName ParameterCategoryName,
        FSUGGraphTextureInput SourceTexture,
        FSUGGraphTextureInput WeightTexture,
        int32 IterationCount = 1
        );
};
