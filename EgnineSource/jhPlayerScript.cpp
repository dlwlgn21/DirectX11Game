#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
	{
	}

	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::PRESSED)
		{
			pos.z -= 3.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
		{
			pos.z += 3.0f * Time::DeltaTime();
		}

		mpTranform->SetPosition(pos);
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
}