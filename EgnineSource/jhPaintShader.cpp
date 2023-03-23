#include "jhPaintShader.h"

namespace jh
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mspTargetTexture()
	{

	}

	void PaintShader::Bind()
	{
		mspTargetTexture->SetUnorderdAccessView(0);
		mThreadGroupX = mspTargetTexture->GetWidth() / mThreadGroupCountX + 1;
		mThreadGroupY = mspTargetTexture->GetHeight() / mThreadGroupCountY + 1;
		mThreadGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		mspTargetTexture->ClearUnorderdAccessView(0);
	}
}