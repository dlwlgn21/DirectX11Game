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
		for (Layer& layer : mLayers)
		{
			layer.Initalize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::AddGameObject(const GameObject* gameObj, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
	}
}