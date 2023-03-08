#pragma once
#include "jhComponent.h"
#include "jhCollider2D.h"

namespace jh
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* pOtherCollider) {};
		virtual void OnCollisionStay(Collider2D* pOtherCollider) {};
		virtual void OnCollisionExit(Collider2D* pOtherCollider) {};

		virtual void OnTriggerEnter(Collider2D* pOtherCollider) {};
		virtual void OnTriggerStay(Collider2D* pOtherCollider) {};
		virtual void OnTriggerExit(Collider2D* pOtherCollider) {};

	private:

	};
}

