#include "jhScene.h"
#include "jhLayer.h"

namespace jh
{
	Scene::Scene()
	{
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
	void Scene::AddGameObject(GameObject* pGameObj, const eLayerType eType)
	{
		mLayers[(UINT)eType].AddGameObject(pGameObj);
	}
}