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
#include "SUGGraphManager.generated.h"

class USUGGraph;

UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class SHADERGRAPHPLUGIN_API USUGGraphManager : public UActorComponent
{
	GENERATED_BODY()

    UPROPERTY()
    USUGGraph* Graph;

    UPROPERTY(EditAnywhere)
    TArray<FSUGGraphOutputRT> RenderTargetPool;

    UPROPERTY()
    TMap<UMaterialInterface*, UMaterialInstanceDynamic*> BasedMIDCacheMap;

    UPROPERTY()
    TMap<FName, UMaterialInstanceDynamic*> NamedMIDCacheMap;

    int32 FindFreeRTIndex(const FRULShaderOutputConfig& OutputConfig);

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(DisplayName="Shader Graph Type"))
    TSubclassOf<USUGGraph> GraphType;

#if WITH_EDITOR
	UFUNCTION(meta=(CallInEditor="true"))
    void CallEditorCustomEvent();

    UFUNCTION(BlueprintImplementableEvent)
	bool EditorCustomEvent();
#endif

    UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetGraphOutput(FName OutputName);

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Execute Graph"))
    void K2_ExecuteGraph(USUGGraph* GraphInstance);

    UFUNCTION(BlueprintCallable, meta=(DisplayName="Clear Outputs"))
    void K2_ClearOutputs();

    void Reset();
    void Initialize(USUGGraph* GraphInstance);
    void Execute();

    UTextureRenderTarget2D* CreateOutputRenderTarget(const FRULShaderOutputConfig& OutputConfig);
    void FindFreeOutputRT(const FRULShaderOutputConfig& OutputConfig, FSUGGraphOutputRT& OutputRT);
    void ClearOutputRTs();

    UMaterialInstanceDynamic* GetCachedMID(UMaterialInterface* BaseMaterial, bool bClearParameterValues = false);
    UMaterialInstanceDynamic* GetCachedMID(FName MaterialName, bool bClearParameterValues = false);
};
