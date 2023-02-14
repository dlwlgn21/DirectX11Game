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
	PlayerScript::~PlayerScript()
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
		//if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		//{
		//	pos.y += 3.0f * Time::DeltaTime();
		//}

		//if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		//{
		//	pos.y -= 3.0f * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		//{
		//	pos.x += 3.0f * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		//{
		//	pos.x -= 3.0f * Time::DeltaTime();
		//}

		//if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		//{
		//	pos.z -= 3.0f * Time::DeltaTime();
		//}

		//if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		//{
		//	pos.z += 3.0f * Time::DeltaTime();
		//}

		mpTranform->SetPosition(pos);
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
}