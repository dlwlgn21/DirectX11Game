#pragma once
#include "jhEntity.h"
#include "jhMath.h"

namespace jh
{

	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;

		Component(const eComponentType eType);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;


		__forceinline eComponentType getType() const		{ return meType; }
		__forceinline void SetOwner(GameObject* pGameObj)	{ assert(pGameObj != nullptr); mpOwner = pGameObj; }

		__forceinline GameObject* GetOwner() const			{ assert(mpOwner != nullptr); return mpOwner; }
		__forceinline UINT GetOrder() const					{ return static_cast<UINT>(meType); }

	protected:
		const eComponentType meType;
		GameObject* mpOwner;
	};
}

