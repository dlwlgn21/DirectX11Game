#include "jhSceneManager.h"
#include "jhScene.h"

namespace jh
{
	void SceneManager::Initalize()
	{
		//mPlayScene = new Scene();
		//mPlayScene->Initalize();

		//GameObject* obj = new GameObject();
		//Transform* tr = new Transform();
		//obj->AddComponent(tr);
		//
		//MeshRenderer* meshRenderer = new MeshRenderer;
		//obj->AddComponent(meshRenderer);

		//mPlayScene->AddGameObject(obj);

	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
}