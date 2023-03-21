#include "jhFadeInScript.h"
#include "jhTime.h"
#include "jhRenderer.h"

namespace jh
{
	FadeinScript::FadeinScript()
		: Script()
		, mAccum(1.0f)
		, mCoefficient(0.5f)
	{
	}

	void FadeinScript::Initialize()
	{

	}
	void FadeinScript::Update()
	{
		//ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::FADE_OUT)];
		//assert(pConstantBuffer != nullptr);

		//renderer::FadeOutConstantBuffer fadeoutConstantBuffer;
		//ZeroMemory(&fadeoutConstantBuffer, sizeof(renderer::FadeOutConstantBuffer));
		//mAccum -= Time::DeltaTime() * mCoefficient;
		//if (mAccum <= 0.0f)
		//{
		//	mAccum = 1.0f;
		//}
		//fadeoutConstantBuffer.fDeltaTime = Vector4(mAccum, 0.0f, 0.0f, 0.0f);

		//pConstantBuffer->WriteConstantBufferAtGPU(&fadeoutConstantBuffer);
		//pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
	void FadeinScript::FixedUpdate()
	{

	}
	void FadeinScript::Render()
	{

	}
}