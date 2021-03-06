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

#include "SUGGraphTypes.h"

FSUGGraphTaskConfig::FSUGGraphTaskConfig()
{
    OutputConfig.SizeX = 0;
    OutputConfig.SizeY = 0;
    OutputConfig.Format = RTF_RGBA16f;
    OutputConfig.bForceLinearGamma = false;

    DrawConfig.BlendType = ERULShaderDrawBlendType::DB_Opaque;
    DrawConfig.bClearRenderTarget = false;
}

FSUGGraphOutputRT::FSUGGraphOutputRT()
    : RefId(nullptr)
    , RenderTarget(nullptr)
{
}

FSUGGraphOutputRT::FSUGGraphOutputRT(UTextureRenderTarget2D* InRenderTarget)
    : RefId(new FRefCountType)
    , RenderTarget(InRenderTarget)
{
}

bool FSUGGraphOutputRT::IsValidOutput() const
{
    return IsValid(RenderTarget) && IsFree();
}

bool FSUGGraphOutputRT::CompareFormat(const FRULShaderOutputConfig& OutputConfig) const
{
    return (
        RenderTarget->SizeX == OutputConfig.SizeX &&
        RenderTarget->SizeY == OutputConfig.SizeY &&
        RenderTarget->GetFormat() == GetPixelFormatFromRenderTargetFormat(OutputConfig.Format)
        );
}

void FSUGGraphOutputRT::ClearReferenceId()
{
    RefId.SafeRelease();
}

void FSUGGraphOutputRT::CreateReferenceId()
{
    ClearReferenceId();
    RefId = new FRefCountType;
}

bool FSUGGraphTextureInput::HasValidInput() const
{
    return IsValid(Texture) || IsValid(Task);
}
