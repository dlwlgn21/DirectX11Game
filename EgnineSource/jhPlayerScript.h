#pragma once
#include "jhScript.h"

namespace jh
{
	class Animator;
	class Transform;
	class PlayerScript final : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		void Start();
		void Complete();
		void End();

	private:
		Transform*				mpTranform;
		Animator*				mpAnimator;
		float					mSpeed;
		const std::wstring		mAnimIdleKey;
		const std::wstring		mAnimMoveKey;
		const std::wstring		mAnimLeftPunchKey;
		const std::wstring		mAnimRightPunchKey;
		bool					mbIsMoving;
		bool					mbIsPunching;
		
	};
}

