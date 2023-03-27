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
		// ��⼭ PaintComputeShader�� 
		// RWTexture2D<float4> tex : register(u0)�� �����. 
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