#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhAnimation.h"

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(10.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimLeftPunchKey(L"PlayerLeftPunch")
		, mAnimRightPunchKey(L"PlayerRightPunch")
		, mpAnimator(nullptr)
		, mbIsMoving(false)
		, mbIsPunching(false)
		, meLookDir(ePlayerLookDirection::RIGHT)
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
		Vector3 prevPos = pos;
		if (mbIsPunching)
		{
			if (mpAnimator->GetCurrentAnimatingAnimation()->IsAnimComplete())
			{
				mbIsPunching = false;
			}
			goto PROCESSING_INPUT;
		}

		if (!Input::IsAnyKeyPressed())
		{
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
			mbIsMoving = false;
		}

PROCESSING_INPUT:
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += mSpeed * Time::DeltaTime();
			mbIsMoving = true;
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= mSpeed * Time::DeltaTime();
			mbIsMoving = true;
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += mSpeed * Time::DeltaTime();
			meLookDir = ePlayerLookDirection::RIGHT;
			mbIsMoving = true;
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= mSpeed * Time::DeltaTime();
			mbIsMoving = true;
			meLookDir = ePlayerLookDirection::LEFT;
		}

		assert(mpAnimator != nullptr);
		if (meLookDir == ePlayerLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}

		if (mbIsMoving && !mbIsPunching)
		{
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::PRESSED)
		{
			pos.z -= mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
		{
			pos.z += mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			mpAnimator->PlayAnimation(mAnimLeftPunchKey, true);
			mbIsPunching = true;
		}
		else if (Input::GetKeyState(eKeyCode::X) == eKeyState::PRESSED)
		{
			mpAnimator->PlayAnimation(mAnimRightPunchKey, true);
			mbIsPunching = true;
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