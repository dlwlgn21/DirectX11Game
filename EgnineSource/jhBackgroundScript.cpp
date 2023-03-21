#include "jhBackgroundScript.h"
#include "jhTime.h"
#include "jhRenderer.h"
#include "jhInput.h"

namespace jh
{
	BackgroundScript::BackgroundScript()
		: Script()
		, mSpeed(1.0f)
		, mUVMove(Vector2::Zero)
	{

	}

	void BackgroundScript::Initialize()
	{

	}
	void BackgroundScript::Update()
	{
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSLATE_UV)];
		assert(pConstantBuffer != nullptr);

		renderer::TranslateUVConstantBuffer translateUVConstantBuffer;
		ZeroMemory(&translateUVConstantBuffer, sizeof(renderer::TranslateUVConstantBuffer));

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			mUVMove.y += mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			mUVMove.y -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			mUVMove.x -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			mUVMove.x += mSpeed * Time::DeltaTime();
		}
		translateUVConstantBuffer.fUVPosition = Vector4(mUVMove.x, mUVMove.y, 0.0f, 0.0f);
		pConstantBuffer->WriteConstantBufferAtGPU(&translateUVConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
	void BackgroundScript::FixedUpdate()
	{

	}
	void BackgroundScript::Render()
	{

	}
}