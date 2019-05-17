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

#include "Tasks/Materials/SUGGraphTask_ErodeFilter.h"
#include "Shaders/RULShaderLibrary.h"
#include "SUGGraph.h"

void USUGGraphTask_ErodeFilter::ExecuteMaterialFunction(USUGGraph& Graph, UMaterialInstanceDynamic& MID)
{
    check(Graph.HasGraphManager());

    ApplyMaterialParameters(MID);

    // Setup parameters multi parameters
    if (IterationCount > 1)
    {
        FSUGGraphOutputRT SwapRT;
        Graph.GetGraphManager()->FindFreeOutputRT(ResolvedOutputConfig, SwapRT);

        TArray<FRULShaderMaterialParameterCollection> ParameterCollections;

        FRULShaderMaterialParameterCollection Pass1;
        Pass1.NamedTextures.Emplace(SourceTextureParameterName, TEXT("__SWAP_TEXTURE__"));
        ParameterCollections.Emplace(Pass1);

        URULShaderLibrary::ApplyMultiParametersMaterial(
            Graph.GetGraphManager(),
            &MID,
            ParameterCollections,
            TaskConfig.DrawConfig,
            Output.RenderTarget,
            SwapRT.RenderTarget,
            1,
            (IterationCount-2)
            );
    }
    // Single iteration
    else
    if (IterationCount > 0)
    {
        URULShaderLibrary::ApplyMaterial(
            Graph.GetGraphManager(),
            &MID,
            Output.RenderTarget,
            TaskConfig.DrawConfig
            );
    }
}
