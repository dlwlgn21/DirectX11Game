#pragma once
#include "jhEntity.h"
#include "jhEnums.h"
#include "jhLayer.h"

namespace jh
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene(const eSceneType eType);
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Release();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* pGameObj, const  eLayerType type);
		__forceinline Layer& GetLayer(const eLayerType eType)				{ return mLayers[static_cast<UINT>(eType)]; }
		eSceneType GetSceneType() const										{ return meSceneType; }
		std::vector<GameObject*> GetAllLayerDontDestroyGameObjects();
		const std::vector<GameObject*>& GetAllGameObjectsFromLayer(const eLayerType eType);
	protected:
		std::vector<Layer> mLayers;
		eSceneType meSceneType;
	};

}