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
		, mSpeed(20.0f)
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
			pos.y += mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::PRESSED)
		{
			pos.z -= mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
		{
			pos.z += mSpeed * Time::DeltaTime();
		}

		mpTranform->SetPosition(pos);
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
	void PlayerScript::OnCollisionEnter(Collider2D* pOtherCollider)
	{
		int a = 0;
	}
	void PlayerScript::OnCollisionStay(Collider2D* pOtherCollider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* pOtherCollider)
	{
	}
	void PlayerScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		int a = 0;
	}
	void PlayerScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		int a = 0;
	}
	void PlayerScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
		int a = 0;
	}
}