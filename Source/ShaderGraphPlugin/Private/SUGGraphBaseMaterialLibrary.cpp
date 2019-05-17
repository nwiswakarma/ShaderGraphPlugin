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

#include "SUGGraphBaseMaterialLibrary.h"

#include "SUGGraph.h"
#include "SUGGraphTask.h"
#include "SUGGraphUtility.h"
#include "Tasks/SUGGraphTask_ApplyMaterial.h"

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddLevelsTask(
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
    float InRemapValueLo,
    float InRemapValueHi,
    float OutRemapValueLo,
    float OutRemapValueHi,
    float MidPoint
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

        MappedScalars.Emplace(TEXT("InRemapValueLo"), InRemapValueLo);
        MappedScalars.Emplace(TEXT("InRemapValueHi"), InRemapValueHi);
        MappedScalars.Emplace(TEXT("OutRemapValueLo"), OutRemapValueLo);
        MappedScalars.Emplace(TEXT("OutRemapValueHi"), OutRemapValueHi);
        MappedScalars.Emplace(TEXT("MidPoint"), MidPoint);
        MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("Levels"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddLevelsManualTask(
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
    float InRemapValueLo,
    float InRemapValueHi,
    float OutRemapValueLo,
    float OutRemapValueHi,
    float LevelsLo,
    float LevelsMi,
    float LevelsHi,
    float MidPoint
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

        MappedScalars.Emplace(TEXT("InRemapValueLo"), InRemapValueLo);
        MappedScalars.Emplace(TEXT("InRemapValueHi"), InRemapValueHi);
        MappedScalars.Emplace(TEXT("OutRemapValueLo"), OutRemapValueLo);
        MappedScalars.Emplace(TEXT("OutRemapValueHi"), OutRemapValueHi);
        MappedScalars.Emplace(TEXT("LevelsLo"), LevelsLo);
        MappedScalars.Emplace(TEXT("LevelsMi"), LevelsMi);
        MappedScalars.Emplace(TEXT("LevelsHi"), LevelsHi);
        MappedScalars.Emplace(TEXT("MidPoint"), MidPoint);
        MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("LevelsManual"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddBlendTargetTask(
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
    float Opacity
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

        MappedScalars.Emplace(TEXT("Opacity"), Opacity);
        MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("BlendTarget"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddBlendTargetMaskedTask(
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
    float Opacity
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

        MappedScalars.Emplace(TEXT("Opacity"), Opacity);
        MappedTextures.Emplace(TEXT("SourceTexture"), SourceTexture);
        MappedTextures.Emplace(TEXT("MaskTexture"), MaskTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("BlendTargetMasked"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddBlendTask(
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
    FSUGGraphTextureInput BackgroundTexture,
    FSUGGraphTextureInput ForegroundTexture,
    float Opacity
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

        MappedScalars.Emplace(TEXT("Opacity"), Opacity);
        MappedTextures.Emplace(TEXT("BackgroundTexture"), BackgroundTexture);
        MappedTextures.Emplace(TEXT("ForegroundTexture"), ForegroundTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("Blend"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphBaseMaterialLibrary::AddBlendMaskedTask(
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
    FSUGGraphTextureInput BackgroundTexture,
    FSUGGraphTextureInput ForegroundTexture,
    FSUGGraphTextureInput MaskTexture,
    float Opacity
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

        MappedScalars.Emplace(TEXT("Opacity"), Opacity);
        MappedTextures.Emplace(TEXT("BackgroundTexture"), BackgroundTexture);
        MappedTextures.Emplace(TEXT("ForegroundTexture"), ForegroundTexture);
        MappedTextures.Emplace(TEXT("MaskTexture"), MaskTexture);

        Task->SetParameters(
            *Graph,
            ParameterCategoryName,
            TEXT("BlendMasked"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}
