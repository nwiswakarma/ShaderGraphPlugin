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
#include "SUGGraphTask.h"
#include "SUGGraphTask_ResolveOutput.generated.h"

class UTextureRenderTarget2D;

UCLASS()
class SHADERGRAPHPLUGIN_API USUGGraphTask_ResolveOutput : public USUGGraphTask
{
	GENERATED_UCLASS_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USUGGraphTask*    SourceTask;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTextureRenderTarget2D* RenderTargetTexture;

    virtual void Initialize(USUGGraph* Graph) override;
    virtual void Execute(USUGGraph* Graph) override;
};
