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

#include "SUGGraphFilterMaterialLibrary.h"

#include "SUGGraph.h"
#include "SUGGraphTask.h"
#include "SUGGraphUtility.h"
#include "Tasks/Materials/SUGGraphTask_BlurFilter1D.h"
#include "Tasks/Materials/SUGGraphTask_ErodeFilter.h"

USUGGraphTask_ApplyMaterial* USUGGraphFilterMaterialLibrary::AddDistanceFilterTask(
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
    float DistanceSteps
    )
{
    USUGGraphTask_ApplyMaterial* Task;
    Task = USUGGraphUtility::AddApplyMaterialTaskWithParameters(
        Graph,
        TaskType,
        TaskConfig,
        ConfigMethod,
        OutputTask,
        MaterialRef,
        ScalarParameters,
        VectorParameters,
        TextureParameters
        );

    if (IsValid(Task))
    {
        TArray<FScalarParam> MappedScalars;
        TArray<FTextureParam> MappedTextures;

        MappedScalars.Emplace(TEXT("DistanceSteps"), DistanceSteps);
        MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);

        check(Graph != nullptr);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("DistanceFilter"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphFilterMaterialLibrary::AddDrawNoiseTask(
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
    FLinearColor ValueRemapRange,
    FLinearColor MaskRemapRange,
    FVector Offset,
    float Scale
    )
{
    USUGGraphTask_ApplyMaterial* Task;
    Task = USUGGraphUtility::AddApplyMaterialTaskWithParameters(
        Graph,
        TaskType,
        TaskConfig,
        ConfigMethod,
        OutputTask,
        MaterialRef,
        ScalarParameters,
        VectorParameters,
        TextureParameters
        );

    if (IsValid(Task))
    {
        TArray<FVectorParam> MappedVectors;
        TArray<FTextureParam> MappedTextures;

        FLinearColor ScaleOffset(Scale, Offset.X, Offset.Y, Offset.Z);

        MappedVectors.Emplace(TEXT("NoiseScaleOffset"), ScaleOffset);
        MappedVectors.Emplace(TEXT("NoiseValueRemapRange"), ValueRemapRange);
        MappedVectors.Emplace(TEXT("NoiseMaskRemapRange"), MaskRemapRange);

        if (SourceTexture.HasValidInput())
        {
            MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);
        }

        if (MaskTexture.HasValidInput())
        {
            MappedTextures.Emplace(TEXT("MaskTexture"), MaskTexture);
        }

        check(Graph != nullptr);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("DrawNoise"),
            { },
            MappedVectors,
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_BlurFilter1D* USUGGraphFilterMaterialLibrary::AddBlurFilter1DTask(
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
    float BlurSampleCount
    )
{
    USUGGraphTask_BlurFilter1D* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_BlurFilter1D>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_BlurFilter1D>(Graph);
        }

        if (IsValid(Task))
        {
            TArray<FScalarParam> MappedScalars;
            TArray<FTextureParam> MappedTextures;

            MappedScalars.Emplace(TEXT("BlurSampleCount"), BlurSampleCount);
            MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);

            Task->MaterialRef = MaterialRef;

            Task->DirectionXParameterName = Graph->GetParameterNameFromCategory(
                ParameterCategoryName,
                TEXT("BlurFilter1D"),
                TEXT("BlurDirectionX")
                );

            Task->DirectionYParameterName = Graph->GetParameterNameFromCategory(
                ParameterCategoryName,
                TEXT("BlurFilter1D"),
                TEXT("BlurDirectionY")
                );

            Task->SourceTextureParameterName = Graph->GetParameterNameFromCategory(
                ParameterCategoryName,
                TEXT("BlurFilter1D"),
                TEXT("SourceTexture")
                );

            Task->SetParameters(
                ScalarParameters,
                VectorParameters,
                TextureParameters
                );

            Task->SetParameters(
                *Graph,
                ParameterCategoryName,
                TEXT("BlurFilter1D"),
                MappedScalars,
                { },
                MappedTextures
                );

            USUGGraphUtility::AddTask(
                *Graph,
                *Task,
                TaskConfig,
                ConfigMethod,
                OutputTask
                );
        }
    }

    return Task;
}

USUGGraphTask_ErodeFilter* USUGGraphFilterMaterialLibrary::AddErodeFilterTask(
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
    int32 IterationCount
    )
{
    USUGGraphTask_ErodeFilter* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_ErodeFilter>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_ErodeFilter>(Graph);
        }

        if (IsValid(Task))
        {
            TArray<FTextureParam> MappedTextures;

            MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);
            MappedTextures.Emplace(TEXT("WeightTexture"), WeightTexture);

            Task->MaterialRef = MaterialRef;
            Task->IterationCount = IterationCount;

            Task->SourceTextureParameterName = Graph->GetParameterNameFromCategory(
                ParameterCategoryName,
                TEXT("ErodeFilter"),
                TEXT("SourceTexture")
                );

            Task->SetParameters(
                ScalarParameters,
                VectorParameters,
                TextureParameters
                );

            Task->SetParameters(
                *Graph,
                ParameterCategoryName,
                TEXT("ErodeFilter"),
                { },
                { },
                MappedTextures
                );

            USUGGraphUtility::AddTask(
                *Graph,
                *Task,
                TaskConfig,
                ConfigMethod,
                OutputTask
                );
        }
    }

    return Task;
}
