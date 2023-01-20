#pragma once
#include "jhEntity.h"
#include "jhComponent.h"
namespace jh
{
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
		virtual void Tick();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* pComponent);

		__forceinline Component* GetComponentOrNull(eComponentType eType)
		{
			Component* pRet = mComponents[static_cast<UINT>(eType)];
			return pRet;
		}

	private:
		std::vector<Component*> mComponents;
	};
}
