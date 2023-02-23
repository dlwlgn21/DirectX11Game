#pragma once
#include "jhEntity.h"
#include "jhTransform.h"

namespace jh
{
	class Component;
	class Script;
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			ACTIVE,
			PAUSED,
			DEAD,
			COUNT
		};


		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* pComponent);

		__forceinline Component* GetComponentOrNull(const eComponentType eType)
		{
			Component* pRet = mComponents[static_cast<UINT>(eType)];
			return pRet;
		}

		__forceinline Transform* GetTransform() const 
		{ 
			assert(mComponents[static_cast<UINT>(eComponentType::TRANSFORM)] != nullptr); 
			return static_cast<Transform*>(mComponents[static_cast<UINT>(eComponentType::TRANSFORM)]); 
		}

		__forceinline bool IsDead() const
		{
			if (meState == eState::DEAD) 
				{return true;}
			return false;
		}

		__forceinline void SetPaused()
		{
			meState = eState::PAUSED;
		}

		__forceinline void SetDead()
		{
			meState = eState::DEAD;
		}

		__forceinline eState GetState() const { return meState; }

	private:
		std::vector<Component*> mComponents;
		std::vector<Script*>	mScripts;
		eState					meState;
	};
}
