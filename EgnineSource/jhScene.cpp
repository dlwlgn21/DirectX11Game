#include "jhScene.h"

namespace jh
{
	Scene::Scene(eSceneType eType)
		: meSceneType(eType)
	{
		mLayers.reserve(static_cast<UINT>(eLayerType::COUNT));
		mLayers.resize(static_cast<UINT>(eLayerType::COUNT));
	}
	Scene::~Scene()
	{
	}
	void Scene::Initalize()
	{
		for (auto& layer : mLayers)
		{
			layer.Initalize();
		}
	}
	void Scene::Update()
	{
		for (auto& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (auto& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (auto& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Release()
	{
		for (auto& layer : mLayers) 
		{
			layer.Release();
		}
	}
	void Scene::Destroy()
	{
		for (auto& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* pGameObj, const eLayerType eType)
	{
		mLayers[static_cast<UINT>(eType)].AddGameObject(pGameObj, eType);
	}

	std::vector<GameObject*> Scene::GetAllLayerDontDestroyGameObjects()
	{
		std::vector<GameObject*> retGameObjects;
		std::vector<std::vector<GameObject*>> allLayerDontDestroyGameObjects;
		allLayerDontDestroyGameObjects.reserve(static_cast<UINT>(eLayerType::COUNT));
		retGameObjects.reserve(32);
		for (auto& layer : mLayers)
		{
			allLayerDontDestroyGameObjects.push_back(layer.GetDontDestroyGameObjects());
		}

		for (std::vector<GameObject*>& vector : allLayerDontDestroyGameObjects)
		{
			for (GameObject* pGameObject : vector)
			{
				assert(pGameObject != nullptr);
				retGameObjects.push_back(pGameObject);
			}
		}

		return retGameObjects;
	}
	const std::vector<GameObject*>& Scene::GetAllGameObjectsFromLayer(const eLayerType eType)
	{
		return mLayers[static_cast<UINT>(eType)].GetGameObjects();
	}
}