#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(20.0f)
		, mAnimIdleKey(L"ZeldaIdle")
		, mAnimMoveKey(L"ZeldaMove")
		, mpAnimator(nullptr)
	{
	}

	void PlayerScript::Initialize()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimMoveKey) = std::bind(&PlayerScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimMoveKey) = std::bind(&PlayerScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimMoveKey) = std::bind(&PlayerScript::End, this);
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

		assert(mpAnimator != nullptr);
		if (Input::GetKeyState(eKeyCode::N_1) == eKeyState::PRESSED)
		{
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
		}

		if (Input::GetKeyState(eKeyCode::N_2) == eKeyState::PRESSED)
		{
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
		}

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
	void PlayerScript::Start()
	{
		int a = 0;
	}
	void PlayerScript::Complete()
	{
		int a = 0;
	}
	void PlayerScript::End()
	{
		int a = 0;
	}
}