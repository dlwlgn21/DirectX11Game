#pragma once
#include "jhComponent.h"

using namespace jh::math;

namespace jh
{
	class Transform final : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void WriteContantBufferAtGPUAndSetConstantBufferAtShader();

		__forceinline void SetPosition(const Vector3 pos)		{ mPosition = pos; }
		__forceinline void SetRotation(const Vector3 rotation)	{ mRotation = rotation; }
		__forceinline void SetScale(const Vector3 scale)		{ mScale = scale; }

		__forceinline Vector3 GetPosition() const				{ return mPosition; }
		__forceinline Vector3 GetRotation() const				{ return mRotation; }
		__forceinline Vector3 GetScale()	const				{ return mScale;	  }

		__forceinline Vector3 GetForward() const				{ return mForwardVector; }
		__forceinline Vector3 GetRight()   const				{ return mRightVector; }
		__forceinline Vector3 GetUp()	   const				{ return mUpVector; }


		__forceinline void			SetParent(Transform* pTransform)			{ assert(pTransform != nullptr); mpParent = pTransform; }
		__forceinline Transform*	GetParent(Transform* pTransform) const		{ return mpParent; }

	private:
		Transform* mpParent;

		Vector3 mForwardVector;
		Vector3 mRightVector;
		Vector3 mUpVector;

		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Matrix mWorldMat;

	};
}
