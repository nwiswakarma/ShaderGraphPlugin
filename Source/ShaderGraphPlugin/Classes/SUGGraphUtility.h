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
#include "Geom/GULGeometryInstanceTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Shaders/RULShaderParameters.h"
#include "SUGGraphTypes.h"
#include "SUGGraphUtility.generated.h"

class UMaterialInterface;
class UTextureRenderTarget2D;
class USUGGraphTask;
class USUGGraphTask_ResolveOutput;
class USUGGraphTask_DrawTaskToOutput;
class USUGGraphTask_DrawTaskToTexture;
class USUGGraphTask_DrawGeometry;
class USUGGraphTask_DrawMaterialPoly;
class USUGGraphTask_DrawMaterialQuad;
class USUGGraphTask_ApplyMaterial;

UCLASS()
class SHADERGRAPHPLUGIN_API USUGGraphUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

    typedef FSUGGraphParameterNameMap FParamNameMap;
    typedef FRULShaderScalarParameter FScalarParam;
    typedef FRULShaderVectorParameter FVectorParam;
    typedef FSUGGraphTextureParameter FTextureParam;

public:

    static void AddTask(
        USUGGraph& Graph,
        USUGGraphTask& Task,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask
        );

    static void AddTask(USUGGraph& Graph, USUGGraphTask& Task);

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", AutoCreateRefTerm="TaskConfig", AdvancedDisplay="Graph,TaskConfig,ConfigMethod,OutputTask"))
    static USUGGraphTask* AddTaskByInstance(
        USUGGraph* Graph,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        USUGGraphTask* TaskInstance
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Resolve Output To Render Target", AutoCreateRefTerm="TaskConfig", AdvancedDisplay="Graph"))
    static USUGGraphTask_ResolveOutput* AddResolveTask(
        USUGGraph* Graph,
        USUGGraphTask* SourceTask,
        UTextureRenderTarget2D* RenderTargetTexture
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Task To Graph Output", AdvancedDisplay="Graph,TaskConfig", AutoCreateRefTerm="TaskConfig"))
    static USUGGraphTask_DrawTaskToOutput* AddDrawTaskToOutputTask(
        USUGGraph* Graph,
        const FSUGGraphTaskConfig& TaskConfig,
        USUGGraphTask* SourceTask,
        FName OutputName
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Task To Texture", AdvancedDisplay="Graph,TaskConfig", AutoCreateRefTerm="TaskConfig"))
    static USUGGraphTask_DrawTaskToTexture* AddDrawTaskToTextureTask(
        USUGGraph* Graph,
        const FSUGGraphTaskConfig& TaskConfig,
        USUGGraphTask* SourceTask,
        UTextureRenderTarget2D* RenderTargetTexture
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Points", AutoCreateRefTerm="TaskConfig,Colors", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask"))
    static USUGGraphTask_DrawGeometry* AddDrawPointsTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_DrawGeometry> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const TArray<FVector2D>& Points,
        const TArray<FColor>& Colors,
        const TArray<int32>& Indices
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Geometry", AutoCreateRefTerm="TaskConfig,Colors", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask"))
    static USUGGraphTask_DrawGeometry* AddDrawGeometryTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_DrawGeometry> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const TArray<FVector>& Vertices,
        const TArray<FColor>& Colors,
        const TArray<int32>& Indices
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", AutoCreateRefTerm="TaskConfig,MaterialRef", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask"))
    static USUGGraphTask_ApplyMaterial* AddApplyMaterialTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", AutoCreateRefTerm="TaskConfig,MaterialRef,ScalarParameters,VectorParameters,TextureParameters", AdvancedDisplay="Graph,TaskType,TaskConfig,ConfigMethod,OutputTask"))
    static USUGGraphTask_ApplyMaterial* AddApplyMaterialTaskWithParameters(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Material Quad", AutoCreateRefTerm="TaskConfig,MaterialRef", AdvancedDisplay="Graph,TaskType,ConfigMethod,OutputTask"))
    static USUGGraphTask_DrawMaterialQuad* AddDrawMaterialQuadTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_DrawMaterialQuad> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FGULQuadGeometryInstance>& Quads
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Material Poly", AutoCreateRefTerm="TaskConfig,MaterialRef", AdvancedDisplay="Graph,TaskType,ConfigMethod,OutputTask"))
    static USUGGraphTask_DrawMaterialPoly* AddDrawMaterialPolyTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_DrawMaterialPoly> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FGULPolyGeometryInstance>& Polys
        );

    UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Graph", DisplayName="Draw Texture Quad", AutoCreateRefTerm="TaskConfig,MaterialRef", AdvancedDisplay="Graph,TaskType,ConfigMethod,OutputTask,ParameterCategoryName"))
    static USUGGraphTask_DrawMaterialQuad* AddDrawTextureQuadTask(
        USUGGraph* Graph,
        TSubclassOf<USUGGraphTask_DrawMaterialQuad> TaskType,
        const FSUGGraphTaskConfig& TaskConfig,
        TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
        USUGGraphTask* OutputTask,
        const FSUGGraphMaterialRef& MaterialRef,
        const TArray<FGULQuadGeometryInstance>& Quads,
        FName ParameterCategoryName,
        FSUGGraphTextureInput SourceTexture,
        float Opacity = 1.f
        );
};
