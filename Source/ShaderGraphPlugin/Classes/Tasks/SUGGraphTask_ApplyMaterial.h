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
#include "Shaders/RULShaderParameters.h"
#include "SUGGraphTask.h"
#include "SUGGraphTypes.h"
#include "SUGGraphTask_ApplyMaterial.generated.h"

class UMaterialInterface;
class UMaterialInstanceDynamic;
class USUGGraph;

UCLASS()
class SHADERGRAPHPLUGIN_API USUGGraphTask_ApplyMaterial : public USUGGraphTask
{
	GENERATED_BODY()

protected:

    UPROPERTY(Transient)
    TMap<FName, UTexture*> ResolvedTextureInputMap;

    virtual void ExecuteMaterialFunction(USUGGraph& Graph, UMaterialInstanceDynamic& MID);

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FSUGGraphMaterialRef MaterialRef;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, float> ScalarInputMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FLinearColor> VectorInputMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FSUGGraphTextureInput> TextureInputMap;

    virtual void Initialize(USUGGraph* Graph) override;
    virtual void Execute(USUGGraph* Graph) override;

    UFUNCTION(BlueprintCallable)
    void SetScalarParameterValue(FName ParameterName, float ParameterValue);

    UFUNCTION(BlueprintCallable)
    void SetVectorParameterValue(FName ParameterName, FLinearColor ParameterValue);

    UFUNCTION(BlueprintCallable)
    void SetTextureParameterValue(FName ParameterName, FSUGGraphTextureInput ParameterValue);

    UFUNCTION(BlueprintCallable)
    void SetScalarParameter(const FRULShaderScalarParameter& Parameter);

    UFUNCTION(BlueprintCallable)
    void SetVectorParameter(const FRULShaderVectorParameter& Parameter);

    UFUNCTION(BlueprintCallable)
    void SetTextureParameter(const FSUGGraphTextureParameter& Parameter);

    void SetParameters(
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters
        );

    void SetParameters(
        const FSUGGraphParameterNameMap& ParameterNameMap,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters
        );

    void SetParameters(
        USUGGraph& Graph,
        FName ParameterCategoryName,
        FName ParameterCategoryDefaultName,
        const TArray<FRULShaderScalarParameter>& ScalarParameters,
        const TArray<FRULShaderVectorParameter>& VectorParameters,
        const TArray<FSUGGraphTextureParameter>& TextureParameters
        );

    void ResolveTaskInputMap();
    void ApplyMaterialParameters(UMaterialInstanceDynamic& MID);
};
