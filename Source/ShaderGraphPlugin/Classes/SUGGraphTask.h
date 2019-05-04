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
#include "SUGGraphTypes.h"
#include "SUGGraphTask.generated.h"

class UTextureRenderTarget2D;
class USUGGraph;

UCLASS(Abstract, BlueprintType, Blueprintable)
class SHADERGRAPHPLUGIN_API USUGGraphTask : public UObject
{
	GENERATED_UCLASS_BODY()

protected:

    struct FDependencyData
    {
        USUGGraphTask* Task;
        FSUGGraphOutputRT Output;

        FDependencyData() : Task(nullptr) {};
        explicit FDependencyData(USUGGraphTask* InTask) : Task(InTask) {}
    };

    FSUGGraphOutputRT Output;
    TArray<FSUGGraphOutputRT*> DependantOutputList;
    TMap<FName, FDependencyData> DependencyMap;

    UPROPERTY()
    USUGGraphTask* OutputTask;

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FSUGGraphTaskConfig TaskConfig;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bRequireOutput;

    UFUNCTION(BlueprintCallable)
    bool IsTaskExecutionValid(const USUGGraph* Graph) const;

    UFUNCTION(BlueprintCallable)
    void SetTaskConfig(const FSUGGraphTaskConfig& InTaskConfig, TEnumAsByte<enum ESUGGraphConfigMethod> InConfigMethod);

    UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Initialize"))
    void K2_Initialize(USUGGraph* Graph);

    virtual void Initialize(USUGGraph* Graph);
    virtual void Execute(USUGGraph* Graph);
    virtual void PostExecute(USUGGraph* Graph);

    FORCEINLINE bool IsOutputRequired() const
    {
        return bRequireOutput;
    }

    FORCEINLINE USUGGraphTask* GetOutputTask() const
    {
        return OutputTask;
    }

    FORCEINLINE bool HasValidOutput() const
    {
        return HasValidOutputRT() && HasValidOutputRefId();
    }

    void SetOutputTask(USUGGraphTask* InOutputTask);
    bool HasValidOutputRT() const;
    bool HasValidOutputRefId() const;

    void GetResolvedOutputConfig(const USUGGraph& Graph, FRULShaderOutputConfig& OutputConfig) const;

    FSUGGraphOutputRT& GetOutputRef();
    void CopyOutputRef(FSUGGraphOutputRT& OutRef);

    void ResolveOutputDependency(const USUGGraph& Graph);
    void LinkOutputDependency(FSUGGraphOutputRT& OutRef);

    UTextureRenderTarget2D* GetOutputRTFromDependencyMap(FName OutputName) const;
};
