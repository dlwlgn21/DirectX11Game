#include "jhFadeOutScript.h"
#include "jhTime.h"
#include "jhRenderer.h"

namespace jh
{
	FadeoutScript::FadeoutScript()
		: Script()
		, mAccum(0.0f)
		, mCoefficient(0.5f)
	{

	}

	void FadeoutScript::Initialize()
	{

	}
	void FadeoutScript::Update()
	{
		//ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::FADE_OUT)];
		//assert(pConstantBuffer != nullptr);

		//renderer::FadeOutConstantBuffer fadeoutConstantBuffer;
		//ZeroMemory(&fadeoutConstantBuffer, sizeof(renderer::FadeOutConstantBuffer));
		//mAccum += Time::DeltaTime() * mCoefficient;
		//if (mAccum >= 1.0f) 
		//{
		//	mAccum = 0.0f;
		//}
		//fadeoutConstantBuffer.fDeltaTime = Vector4(mAccum, 0.0f, 0.0f, 0.0f);
		//
		//pConstantBuffer->WriteConstantBufferAtGPU(&fadeoutConstantBuffer);
		//pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
	void FadeoutScript::FixedUpdate()
	{

	}
	void FadeoutScript::Render()
	{

	}
}