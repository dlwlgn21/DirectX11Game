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
			if (pGameObj->GetState() != GameObject::eState::ACTIVE)
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
			if (pGameObj->GetState() != GameObject::eState::ACTIVE)
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
			if (pGameObj->GetState() != GameObject::eState::ACTIVE)
				{continue;}
			pGameObj->Render();
		}
	}

	void Layer::Release()
	{
		for (auto* pGameObj : mGameObjects)
		{
			if (pGameObj == nullptr)
				{continue;}
			delete pGameObj;
		}
		mGameObjects.clear();
	}

	void Layer::Destroy()
	{
		std::unordered_set<GameObject*> deletingGameIObjects;
		deletingGameIObjects.reserve(MAX_GAME_OBJECT_COUNT);
		// 삭제할 오브젝트들을 전부 찾아온다.
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject->GetState() == GameObject::eState::DEAD)
			{
				deletingGameIObjects.insert(pGameObject);
			}
		}

		// 지워야할 오브젝트 지워줌.
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end();)
		{
			auto deleteIter = deletingGameIObjects.find(*iter);
			if (deleteIter != deletingGameIObjects.end())
			{
				mGameObjects.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		// 삭제할 오브젝트들 실제 램에서 삭제.
		for (auto* pGameObject : deletingGameIObjects)
		{
			delete pGameObject;
		}
	}

	void Layer::AddGameObject(GameObject* pGameObj, const eLayerType eType)
	{
		assert(pGameObj != nullptr);
		mGameObjects.push_back(pGameObj);
		pGameObj->SetLayerType(eType);
		
	}
	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> retGameObjs;
		retGameObjs.reserve(16);
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end();)
		{
			if ((*iter)->IsDontDestroy())
			{
				retGameObjs.push_back(*iter);
				mGameObjects.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		return retGameObjs;
	}
}