#pragma once
#include "jhComponent.h"
#include "jhTransform.h"

namespace jh
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		virtual ~Collider2D();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetType(const eColliderType eType) { meColliderType = eType; }
		eColliderType GetColliderType() const	{ return meColliderType; }
		void SetSize(const Vector2 size)		{ mSize = size; }
		Vector2 GetSize() const					{ return mSize; }
		void SetCenter(const Vector2 center)	{ mCenter = center; }
		bool GetIsUsePhysics() const			{ return mbIsUsePhysics; }
		UINT GetColliderID() const				{ return mUniqueColliderNumber; }
		Vector3 GetPosition() const				{ return mPosition; }
		void SetRadius(const float radius)		{ mRadius = radius; }
		float GetRadius() const					{ return mRadius; }


		virtual void OnCollisionEnter(Collider2D* pOtherCollider);
		virtual void OnCollisionStay(Collider2D* pOtherCollider);
		virtual void OnCollisionExit(Collider2D* pOtherCollider);

		virtual void OnTriggerEnter(Collider2D* pOtherCollider);
		virtual void OnTriggerStay(Collider2D* pOtherCollider);
		virtual void OnTriggerExit(Collider2D* pOtherCollider);

	private:
		static UINT		sTotalColliderCount;
		UINT			mUniqueColliderNumber;
		eColliderType	meColliderType;
		Transform*		mpTransform;

		Vector2			mSize;
		Vector2			mCenter;
		Vector3			mPosition;
		float			mRadius;
		bool			mbIsUsePhysics;
	};
}

