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
		mScenes[static_cast<UINT>(eSceneType::PLAY)] = new PlayScene();

		mpPlayScene = mScenes[static_cast<UINT>(eSceneType::PLAY)];

		mpPlayScene->Initalize();
		mScenes[static_cast<UINT>(eSceneType::TITLE)]->Initalize();
	}

	void SceneManager::Update()
	{
		mpPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mpPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mpPlayScene->Render();
	}

	void SceneManager::Destroy()
	{
		mpPlayScene->Destroy();
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
		assert(mpPlayScene != nullptr);
		mpPlayScene->OnExit();

		// 씬이 바뀔때, Dontdestroy 오브젝트는 다음씬으로 같이 넘겨주어야 함.
		std::vector<GameObject*> allLayerDondestroyGameObjects = mpPlayScene->GetAllLayerDontDestroyGameObjects();
		mpPlayScene = mScenes[static_cast<UINT>(eType)];

		for (auto* pGameObject : allLayerDondestroyGameObjects)
		{
			assert(pGameObject != nullptr);
			mpPlayScene->AddGameObject(pGameObject, pGameObject->GetLayerType());
		}

		assert(mpPlayScene != nullptr);
		mpPlayScene->OnEnter();
	}

}