#pragma once
#include "jhEntity.h"
#include "jhEnums.h"

namespace jh
{
	class Layer;
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(const GameObject* gameObj, const eLayerType type);

	private:
		std::vector<Layer> mLayers;
	};

}