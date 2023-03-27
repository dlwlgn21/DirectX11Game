#include "jhPaintShader.h"

namespace jh
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mpTargetTexture(nullptr)
	{

	}

	void PaintShader::Bind()
	{
		assert(mpTargetTexture != nullptr);
		// 요기서 PaintComputeShader의 
		// RWTexture2D<float4> tex : register(u0)와 연결됨. 
		mpTargetTexture->SetUnorderdAccessView(0);
		mThreadGroupX = mpTargetTexture->GetWidth() / mThreadGroupCountX + 1;
		mThreadGroupY = mpTargetTexture->GetHeight() / mThreadGroupCountY + 1;
		mThreadGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		assert(mpTargetTexture != nullptr);
		mpTargetTexture->ClearUnorderdAccessView(0);
	}
}