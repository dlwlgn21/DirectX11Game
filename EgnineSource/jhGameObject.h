#pragma once
#include "jhEntity.h"

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

	private:
		std::vector<Component*> mComponents;
		std::vector<Script*>	mScripts;
		eState					meState;
	};
}
