#include "jhScene.h"

namespace jh
{
	Scene::Scene()
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
	void Scene::AddGameObject(GameObject* pGameObj, const eLayerType eType)
	{
		mLayers[static_cast<UINT>(eType)].AddGameObject(pGameObj);
	}
}