#include "jhLayer.h"
#include "jhGameObject.h"

constexpr const int MAX_GAME_OBJECT_COUNT = 128;
namespace jh
{
	Layer::Layer()
	{
		mGameObjects.reserve(MAX_GAME_OBJECT_COUNT);
	}

	Layer::~Layer()
	{
	}

	void Layer::Initalize()
	{
		for (auto* pGameObj : mGameObjects)
		{
			if (pGameObj == nullptr) 
				{continue;}
			pGameObj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (auto* pGameObj : mGameObjects)
		{
			if (pGameObj == nullptr)
				{continue;}
			pGameObj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (auto* pGameObj : mGameObjects)
		{
			if (pGameObj == nullptr)
				{continue;}
			pGameObj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (auto* pGameObj : mGameObjects)
		{
			if (pGameObj == nullptr)
				{continue;}
			pGameObj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* pGameObj)
	{
		assert(pGameObj != nullptr);
		mGameObjects.push_back(pGameObj);
	}
}