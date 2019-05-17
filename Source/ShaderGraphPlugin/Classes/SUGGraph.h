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
#include "SUGGraph.generated.h"

class UMaterialInterface;
class USUGGraphTask;
class USUGGraphManager;

USTRUCT(BlueprintType)
struct SHADERGRAPHPLUGIN_API FSUGGraphOutputEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRULShaderOutputConfig OutputConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<enum ESUGGraphConfigMethod> ConfigMethod = RUL_CM_Parent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTextureRenderTarget2D* RenderTarget;
};

UCLASS(BlueprintType, Blueprintable)
class SHADERGRAPHPLUGIN_API USUGGraph : public UObject
{
	GENERATED_UCLASS_BODY()

    UPROPERTY(Transient)
    USUGGraphManager* GraphManager;

    TArray<USUGGraphTask*> TaskQueue;
    bool bExecutionInProgress = false;

    void AssignOutput(USUGGraphTask& Task);
    void InitializeTasks();
    void ExecuteTasks();

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRULShaderOutputConfig OutputConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FSUGGraphParameterNameMap> ParameterNameMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FSUGGraphOutputEntry> OutputMap;

    UFUNCTION(BlueprintCallable)
    void AddTask(USUGGraphTask* Task);

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Has Valid Dimension"))
    bool K2_HasValidDimension() const;

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Is Execution In Progress"))
    bool K2_IsExecutionInProgress() const;

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Has Graph Manager"))
    bool K2_HasGraphManager() const;

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Get Graph Manager"))
    USUGGraphManager* K2_GetGraphManager() const;

    UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Prepare Graph"))
	bool K2_PrepareGraph(USUGGraphManager* InGraphManager);

    UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetOutputRenderTarget(FName OutputName);

    FORCEINLINE bool HasValidDimension() const
    {
        return OutputConfig.SizeX > 0 && OutputConfig.SizeY > 0;
    }

    FORCEINLINE bool IsExecutionInProgress() const
    {
        return bExecutionInProgress;
    }

    FORCEINLINE USUGGraphManager* GetGraphManager() const
    {
        return GraphManager;
    }

    FORCEINLINE const FSUGGraphParameterNameMap* GetParameterNameMap(FName ParameterCategoryName) const
    {
        return ParameterNameMap.Find(ParameterCategoryName);
    }

    FORCEINLINE FName GetParameterNameFromCategory(
        FName ParameterCategoryName,
        FName ParameterCategoryDefaultName,
        FName ParameterNameKey,
        bool bUseParameterNameKeyAsDefault = true
        ) const
    {
        if (! ParameterCategoryName.IsValid())
        {
            ParameterCategoryName = ParameterCategoryDefaultName;
        }

        const FSUGGraphParameterNameMap* ParameterCategory = GetParameterNameMap(ParameterCategoryName);
        const FName DefaultName = bUseParameterNameKeyAsDefault
            ? ParameterNameKey
            : FName();

        return ParameterCategory
            ? ParameterCategory->GetOrDefault(ParameterNameKey)
            : DefaultName;
    }

    UMaterialInstanceDynamic* GetCachedMID(UMaterialInterface* BaseMaterial, bool bClearParameterValues = false);
    UMaterialInstanceDynamic* GetCachedMID(FName MaterialName, bool bClearParameterValues = false);

    bool HasGraphManager() const;
    void ExecuteGraph(USUGGraphManager* InGraphManager);

	void GetOutputConfig(FRULShaderOutputConfig& OutConfig) const;
	FSUGGraphOutputEntry* GetOutput(FName OutputName);
	UTextureRenderTarget2D* CreateOutputRenderTarget(FName OutputName, const FRULShaderOutputConfig& InOutputConfig);
};
