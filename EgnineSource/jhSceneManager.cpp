#include "jhSceneManager.h"
#include "jhTitleScene.h"
#include "jhPlayScene.h"
#include "jhGameObject.h"

namespace jh
{

	void SceneManager::Initalize()
	{
		//mpPlayScene->Initalize();

		mScenes.reserve(static_cast<UINT>(eSceneType::COUNT));
		mScenes.resize(static_cast<UINT>(eSceneType::COUNT));

		mScenes[static_cast<UINT>(eSceneType::TITLE)] = new TitleScene();
		//mScenes[static_cast<UINT>(eSceneType::PLAY)] = new PlayScene();

		mpCurrentScene = mScenes[static_cast<UINT>(eSceneType::TITLE)];
		mpCurrentScene->Initalize();
		//for (UINT i = 0; i < static_cast<UINT>(eSceneType::COUNT) - 1; ++i)
		//{
		//	mScenes[i]->Initalize();
		//}
	}

	void SceneManager::Update()
	{
		mpCurrentScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mpCurrentScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mpCurrentScene->Render();
	}

	void SceneManager::Destroy()
	{
		mpCurrentScene->Destroy();
	}

	void SceneManager::Release()
	{
		//mpPlayScene->Release();
		//delete mpPlayScene;

		for (auto* pScene : mScenes)
		{
			if (pScene != nullptr)
			{
				pScene->Release();
				delete pScene;
			}
		}

		mScenes.clear();
	}

	void SceneManager::LoadScene(eSceneType eType)
	{
		assert(mpCurrentScene != nullptr);
		mpCurrentScene->OnExit();

		// 씬이 바뀔때, Dontdestroy 오브젝트는 다음씬으로 같이 넘겨주어야 함.
		std::vector<GameObject*> allLayerDondestroyGameObjects = mpCurrentScene->GetAllLayerDontDestroyGameObjects();
		mpCurrentScene = mScenes[static_cast<UINT>(eType)];

		for (auto* pGameObject : allLayerDondestroyGameObjects)
		{
			assert(pGameObject != nullptr);
			mpCurrentScene->AddGameObject(pGameObject, pGameObject->GetLayerType());
		}

		assert(mpCurrentScene != nullptr);
		mpCurrentScene->OnEnter();
	}

}