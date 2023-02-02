#include "jhSceneManager.h"
#include "jhScene.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"

namespace jh
{

	Scene* SceneManager::mpPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mpPlayScene = new Scene();
		mpPlayScene->Initalize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(-0.2f, 0.2f, 0.2f));
		obj->AddComponent(tr);
		MeshRenderer* meshRenderer = new MeshRenderer;
		meshRenderer->SetShader(renderer::pShader);
		meshRenderer->SetMesh(renderer::pMesh);
		obj->AddComponent(meshRenderer);
		
		mpPlayScene->AddGameObject(obj, eLayerType::PLAYER);
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
}