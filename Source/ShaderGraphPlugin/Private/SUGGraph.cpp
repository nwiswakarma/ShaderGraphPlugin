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

#include "SUGGraph.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Shaders/RULShaderLibrary.h"
#include "SUGGraphManager.h"
#include "SUGGraphTask.h"

USUGGraph::USUGGraph(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OutputConfig.SizeX = 256;
	OutputConfig.SizeY = 256;
	OutputConfig.Format = RTF_RGBA16f;
	OutputConfig.bForceLinearGamma = false;
}

void USUGGraph::AddTask(USUGGraphTask* Task)
{
    if (IsExecutionInProgress())
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraph::AddTask() ABORTED, GRAPH EXECUTION IS IN PROGRESS"));
        return;
    }
    else
    if (IsValid(Task))
    {
        TaskQueue.Emplace(Task);
    }
}

bool USUGGraph::HasGraphManager() const
{
    return IsValid(GraphManager);
}

bool USUGGraph::K2_HasValidDimension() const
{
    return HasValidDimension();
}

bool USUGGraph::K2_IsExecutionInProgress() const
{
    return IsExecutionInProgress();
}

bool USUGGraph::K2_HasGraphManager() const
{
    return HasGraphManager();
}

USUGGraphManager* USUGGraph::K2_GetGraphManager() const
{
    return GetGraphManager();
}

void USUGGraph::GetOutputConfig(FRULShaderOutputConfig& OutConfig) const
{
    OutConfig = OutputConfig;
}

void USUGGraph::AssignOutput(USUGGraphTask& Task)
{
    check(HasGraphManager());

    // Assign output from free output
    if (! Task.HasValidOutput())
    {
        FRULShaderOutputConfig TaskOutputConfig;
        Task.GetResolvedOutputConfig(TaskOutputConfig);

        GraphManager->FindFreeOutputRT(TaskOutputConfig, Task.GetOutputRef());
    }
}

FSUGGraphOutputEntry* USUGGraph::GetOutput(FName OutputName)
{
    return OutputMap.Find(OutputName);
}

UTextureRenderTarget2D* USUGGraph::CreateOutputRenderTarget(FName OutputName, const FRULShaderOutputConfig& InOutputConfig)
{
    FSUGGraphOutputEntry* OutputEntry = OutputMap.Find(OutputName);

    if (OutputEntry && HasGraphManager())
    {
        OutputEntry->RenderTarget = GraphManager->CreateOutputRenderTarget(InOutputConfig);
        return OutputEntry->RenderTarget;
    }
    else
    {
        return nullptr;
    }
}

UTextureRenderTarget2D* USUGGraph::GetOutputRenderTarget(FName OutputName)
{
    FSUGGraphOutputEntry* OutputEntry = OutputMap.Find(OutputName);

    if (OutputEntry)
    {
        return OutputEntry->RenderTarget;
    }
    else
    {
        return nullptr;
    }
}

UMaterialInstanceDynamic* USUGGraph::GetCachedMID(UMaterialInterface* BaseMaterial, bool bClearParameterValues)
{
    if (! GraphManager)
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::GetCachedMID() ABORTED, GRAPH MANAGER HAS NOT BEEN ASSIGNED! MAKE SURE TO CALL DURING Execute()"));
        return nullptr;
    }
    else
    if (! IsValid(BaseMaterial))
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::GetCachedMID() ABORTED, INVALID BASE MATERIAL"));
        return nullptr;
    }

    return GraphManager->GetCachedMID(BaseMaterial, bClearParameterValues);
}

UMaterialInstanceDynamic* USUGGraph::GetCachedMID(FName MaterialName, bool bClearParameterValues)
{
    if (! GraphManager)
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::GetCachedMID() ABORTED, GRAPH MANAGER HAS NOT BEEN ASSIGNED! MAKE SURE TO CALL DURING Execute()"));
        return nullptr;
    }

    return GraphManager->GetCachedMID(MaterialName, bClearParameterValues);
}

void USUGGraph::ExecuteGraph(USUGGraphManager* InGraphManager)
{
    if (! IsValid(InGraphManager))
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::ExecuteGraph() ABORTED, INVALID GRAPH MANAGER"));
    }
    else
    if (! HasValidDimension())
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::ExecuteGraph() ABORTED, INVALID DIMENSION"));
    }
    if (IsExecutionInProgress())
    {
        UE_LOG(LogSGP,Warning, TEXT("USUGGraphUtility::ExecuteGraph() ABORTED, GRAPH EXECUTION IS IN PROGRESS"));
    }
    else
    {
        GraphManager = InGraphManager;

        InitializeTasks();
        ExecuteTasks();

        GraphManager = nullptr;
    }
}

void USUGGraph::InitializeTasks()
{
    for (int32 i=0; i<TaskQueue.Num(); ++i)
    {
        USUGGraphTask* Task = TaskQueue[i];

        if (IsValid(Task))
        {
            Task->Initialize(this);
            Task->K2_Initialize(this);
            Task->ResolveOutputConfig(*this);
            Task->ResolveOutputDependency(*this);
        }
    }
}

void USUGGraph::ExecuteTasks()
{
    for (int32 i=0; i<TaskQueue.Num(); ++i)
    {
        USUGGraphTask* Task = TaskQueue[i];

        if (IsValid(Task))
        {
            if (Task->IsOutputRequired())
            {
                AssignOutput(*Task);
            }

            Task->Execute(this);
            Task->PostExecute(this);
        }
    }
}
