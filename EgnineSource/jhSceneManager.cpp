#include "jhSceneManager.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhTexture.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhPlayerScript.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhSpriteRenderer.h"

namespace jh
{

	Scene* SceneManager::mpPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mpPlayScene = new Scene();
		mpPlayScene->Initalize();

		// Camera Game Obj
		GameObject* pCameraObj = new GameObject();
		Transform* pCameraTransform = new Transform();
		pCameraTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		pCameraObj->AddComponent(pCameraTransform);
		Camera* pCameraComponent = new Camera();
		pCameraObj->AddComponent(pCameraComponent);
		mpPlayScene->AddGameObject(pCameraObj, eLayerType::CAMERA);
		CameraScript* pCameraScript = new CameraScript();
		pCameraObj->AddComponent(pCameraScript);



		// Jenaro
		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
		obj->AddComponent(tr);

		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		Material* pMaterial = Resources::Find<Material>(L"RectMaterial");
		assert(pMaterial != nullptr);
		pMeshRenderer->SetMaterial(pMaterial);
		pMaterial->SetRenderingMode(eRenderingMode::OPAQUEE);
		obj->AddComponent(pMeshRenderer);
		
		//PlayerScript* pPlayerScript = new PlayerScript();
		//obj->AddComponent(pPlayerScript);

		mpPlayScene->AddGameObject(obj, eLayerType::PLAYER);

		// Another Jenaro
		GameObject* pSriteObj = new GameObject();
		Transform* pTransform = new Transform();
		pTransform->SetPosition(Vector3(10.0f, 0.0f, 20.0f));
		pSriteObj->AddComponent(pTransform);

		SpriteRenderer* pSpriteRenderer = new SpriteRenderer;

		pSpriteRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		Material* pSpriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		assert(pSpriteMaterial != nullptr);
		pSpriteMaterial->SetRenderingMode(eRenderingMode::TRANSPARENTT);
		pSpriteRenderer->SetMaterial(pSpriteMaterial);
		pSriteObj->AddComponent(pSpriteRenderer);

		//PlayerScript* pPlayerScript = new PlayerScript();
		//obj->AddComponent(pPlayerScript);

		mpPlayScene->AddGameObject(pSriteObj, eLayerType::PLAYER);

		mpPlayScene->Initalize();
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
	void SceneManager::Release()
	{
		mpPlayScene->Release();
		delete mpPlayScene;
	}
}