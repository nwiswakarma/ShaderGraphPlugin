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

#include "SUGGraphUtility.h"

#include "Engine/TextureRenderTarget2D.h"
#include "SUGGraphTask.h"
#include "Tasks/SUGGraphTask_ApplyMaterial.h"
#include "Tasks/SUGGraphTask_DrawGeometry.h"
#include "Tasks/SUGGraphTask_DrawMaterialPoly.h"
#include "Tasks/SUGGraphTask_DrawMaterialQuad.h"
#include "Tasks/SUGGraphTask_DrawTaskToOutput.h"
#include "Tasks/SUGGraphTask_DrawTaskToTexture.h"
#include "Tasks/SUGGraphTask_ResolveOutput.h"

void USUGGraphUtility::AddTask(
    USUGGraph& Graph,
    USUGGraphTask& Task,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask
    )
{
    Task.SetTaskConfig(TaskConfig, ConfigMethod);
    Task.SetOutputTask(OutputTask);
    Graph.AddTask(&Task);
}

void USUGGraphUtility::AddTask(USUGGraph& Graph, USUGGraphTask& Task)
{
    Graph.AddTask(&Task);
}

USUGGraphTask* USUGGraphUtility::AddTaskByInstance(
    USUGGraph* Graph,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    USUGGraphTask* TaskInstance
    )
{
    if (IsValid(Graph) && IsValid(TaskInstance))
    {
        AddTask(*Graph, *TaskInstance, TaskConfig, ConfigMethod, OutputTask);
    }

    return TaskInstance;
}

USUGGraphTask_ResolveOutput* USUGGraphUtility::AddResolveTask(
    USUGGraph* Graph,
    USUGGraphTask* SourceTask,
    UTextureRenderTarget2D* RenderTargetTexture
    )
{
    USUGGraphTask_ResolveOutput* Task = nullptr;

    if (IsValid(Graph))
    {
        Task = NewObject<USUGGraphTask_ResolveOutput>(Graph);

        if (IsValid(Task))
        {
            Task->SourceTask = SourceTask;
            Task->RenderTargetTexture = RenderTargetTexture;
            AddTask(*Graph, *Task);
        }
    }

    return Task;
}

USUGGraphTask_DrawTaskToOutput* USUGGraphUtility::AddDrawTaskToOutputTask(
    USUGGraph* Graph,
    const FSUGGraphTaskConfig& TaskConfig,
    USUGGraphTask* SourceTask,
    FName OutputName
    )
{
    USUGGraphTask_DrawTaskToOutput* Task = nullptr;

    if (IsValid(Graph))
    {
        Task = NewObject<USUGGraphTask_DrawTaskToOutput>(Graph);

        if (IsValid(Task))
        {
            Task->SourceTask = SourceTask;
            Task->OutputName = OutputName;
            Task->TaskConfig.DrawConfig = TaskConfig.DrawConfig;
            AddTask(*Graph, *Task);
        }
    }

    return Task;
}

USUGGraphTask_DrawTaskToTexture* USUGGraphUtility::AddDrawTaskToTextureTask(
    USUGGraph* Graph,
    const FSUGGraphTaskConfig& TaskConfig,
    USUGGraphTask* SourceTask,
    UTextureRenderTarget2D* RenderTargetTexture
    )
{
    USUGGraphTask_DrawTaskToTexture* Task = nullptr;

    if (IsValid(Graph))
    {
        Task = NewObject<USUGGraphTask_DrawTaskToTexture>(Graph);

        if (IsValid(Task))
        {
            Task->SourceTask = SourceTask;
            Task->RenderTargetTexture = RenderTargetTexture;
            Task->TaskConfig.DrawConfig = TaskConfig.DrawConfig;
            AddTask(*Graph, *Task);
        }
    }

    return Task;
}

USUGGraphTask_DrawGeometry* USUGGraphUtility::AddDrawPointsTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_DrawGeometry> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const TArray<FVector2D>& Points,
    const TArray<FColor>& Colors,
    const TArray<int32>& Indices,
    FIntPoint Dimension
    )
{
    USUGGraphTask_DrawGeometry* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_DrawGeometry>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_DrawGeometry>(Graph);
        }

        if (IsValid(Task))
        {
            TArray<FVector> Vertices;
            Vertices.Reserve(Points.Num());

            for (int32 i=0; i<Points.Num(); ++i)
            {
                Vertices.Emplace(Points[i], 1.f);
            }

            Task->Vertices = Vertices;
            Task->Colors = Colors;
            Task->Indices = Indices;
            Task->Dimension = Dimension;

            AddTask(*Graph, *Task, TaskConfig, ConfigMethod, OutputTask);
        }
    }

    return Task;
}

USUGGraphTask_DrawGeometry* USUGGraphUtility::AddDrawGeometryTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_DrawGeometry> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const TArray<FVector>& Vertices,
    const TArray<FColor>& Colors,
    const TArray<int32>& Indices,
    FIntPoint Dimension
    )
{
    USUGGraphTask_DrawGeometry* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_DrawGeometry>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_DrawGeometry>(Graph);
        }

        if (IsValid(Task))
        {
            Task->Vertices = Vertices;
            Task->Colors = Colors;
            Task->Indices = Indices;
            Task->Dimension = Dimension;
            AddTask(*Graph, *Task, TaskConfig, ConfigMethod, OutputTask);
        }
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphUtility::AddApplyMaterialTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const FSUGGraphMaterialRef& MaterialRef
    )
{
    USUGGraphTask_ApplyMaterial* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_ApplyMaterial>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_ApplyMaterial>(Graph);
        }

        if (IsValid(Task))
        {
            Task->MaterialRef = MaterialRef;
            AddTask(*Graph, *Task, TaskConfig, ConfigMethod, OutputTask);
        }
    }

    return Task;
}

USUGGraphTask_ApplyMaterial* USUGGraphUtility::AddApplyMaterialTaskWithParameters(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_ApplyMaterial> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const FSUGGraphMaterialRef& MaterialRef,
    const TArray<FRULShaderScalarParameter>& ScalarParameters,
    const TArray<FRULShaderVectorParameter>& VectorParameters,
    const TArray<FSUGGraphTextureParameter>& TextureParameters
    )
{
    USUGGraphTask_ApplyMaterial* Task;
    Task = AddApplyMaterialTask(
        Graph,
        TaskType,
        TaskConfig,
        ConfigMethod,
        OutputTask,
        MaterialRef
        );

    if (IsValid(Task))
    {
        Task->SetParameters(ScalarParameters, VectorParameters, TextureParameters);
    }

    return Task;
}

USUGGraphTask_DrawMaterialQuad* USUGGraphUtility::AddDrawMaterialQuadTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_DrawMaterialQuad> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const FSUGGraphMaterialRef& MaterialRef,
    const TArray<FGULQuadGeometryInstance>& Quads
    )
{
    USUGGraphTask_DrawMaterialQuad* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_DrawMaterialQuad>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_DrawMaterialQuad>(Graph);
        }

        if (IsValid(Task))
        {
            Task->MaterialRef = MaterialRef;
            Task->Quads = Quads;
            AddTask(*Graph, *Task, TaskConfig, ConfigMethod, OutputTask);
        }
    }

    return Task;
}

USUGGraphTask_DrawMaterialPoly* USUGGraphUtility::AddDrawMaterialPolyTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_DrawMaterialPoly> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const FSUGGraphMaterialRef& MaterialRef,
    const TArray<FGULPolyGeometryInstance>& Polys
    )
{
    USUGGraphTask_DrawMaterialPoly* Task = nullptr;

    if (IsValid(Graph))
    {
        if (TaskType.Get())
        {
            Task = NewObject<USUGGraphTask_DrawMaterialPoly>(Graph, TaskType);
        }
        else
        {
            Task = NewObject<USUGGraphTask_DrawMaterialPoly>(Graph);
        }

        if (IsValid(Task))
        {
            Task->MaterialRef = MaterialRef;
            Task->Polys = Polys;
            AddTask(*Graph, *Task, TaskConfig, ConfigMethod, OutputTask);
        }
    }

    return Task;
}

USUGGraphTask_DrawMaterialQuad* USUGGraphUtility::AddDrawTextureQuadTask(
    USUGGraph* Graph,
    TSubclassOf<USUGGraphTask_DrawMaterialQuad> TaskType,
    const FSUGGraphTaskConfig& TaskConfig,
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod,
    USUGGraphTask* OutputTask,
    const FSUGGraphMaterialRef& MaterialRef,
    const TArray<FGULQuadGeometryInstance>& Quads,
    FName ParameterCategoryName,
    FSUGGraphTextureInput SourceTexture,
    float Opacity
    )
{
    USUGGraphTask_DrawMaterialQuad* Task;
    Task = AddDrawMaterialQuadTask(
        Graph,
        TaskType,
        TaskConfig,
        ConfigMethod,
        OutputTask,
        MaterialRef,
        Quads
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
            TEXT("DrawTextureQuad"),
            MappedScalars,
            { },
            MappedTextures
            );
    }

    return Task;
}
