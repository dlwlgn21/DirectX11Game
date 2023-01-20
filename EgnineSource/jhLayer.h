#pragma once
#include "jhEntity.h"

namespace jh
{
	class GameObject;
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(const GameObject* gameObject);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
