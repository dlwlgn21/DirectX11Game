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
		//mpPlayScene->Initalize();

		// Camera Game Obj
		GameObject* pCameraObj = new GameObject();
		Transform* pCameraTransform = new Transform();
		pCameraTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		pCameraObj->AddComponent(pCameraTransform);
		Camera* pCameraComponent = new Camera();
		pCameraObj->AddComponent(pCameraComponent);
		pCameraComponent->TurnLayerMasks(eLayerType::UI, false);
		mpPlayScene->AddGameObject(pCameraObj, eLayerType::CAMERA);
		CameraScript* pCameraScript = new CameraScript();
		pCameraObj->AddComponent(pCameraScript);

		//Camera UI Game Obj
		GameObject* pCameraUIObj = new GameObject();
		Transform* pCameraUITransform = new Transform();
		pCameraUITransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		pCameraUIObj->AddComponent(pCameraUITransform);
		Camera* pCameraUIComponent = new Camera();
		pCameraUIComponent->setProjectionType(Camera::eProjectionType::ORTHOGRAPHIC);
		pCameraUIComponent->DisableAllLayerMasks();
		pCameraUIComponent->TurnLayerMasks(eLayerType::UI, true);
		pCameraUIObj->AddComponent(pCameraUIComponent); 
		mpPlayScene->AddGameObject(pCameraUIObj, eLayerType::CAMERA);
		



		// Gennaro
		GameObject* pGenaroObj = new GameObject();
		Transform* pGenaroTransform = new Transform();
		pGenaroTransform->SetPosition(Vector3(-3.0f, 0.0f, 20.0f));
		pGenaroTransform->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		pGenaroObj->AddComponent(pGenaroTransform);

		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Resources::Find<Material>(DEFAULT_MATERIAL_KEY));
		pGenaroObj->AddComponent(pMeshRenderer);
		
		PlayerScript* pPlayerScript = new PlayerScript();
		pGenaroObj->AddComponent(pPlayerScript);

		mpPlayScene->AddGameObject(pGenaroObj, eLayerType::PLAYER);

		// Gennaro Child
		GameObject* pGenaroChild = new GameObject();
		Transform* pGenaroChildTransform = new Transform();
		pGenaroChildTransform->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		pGenaroChild->AddComponent(pGenaroChildTransform);
		pGenaroChildTransform->SetParent(pGenaroTransform);
		MeshRenderer* pGenaroChildMeshRenderer = new MeshRenderer();
		pGenaroChildMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pGenaroChildMeshRenderer->SetMaterial(Resources::Find<Material>(DEFAULT_MATERIAL_KEY));
		pGenaroChild->AddComponent(pGenaroChildMeshRenderer);

		//PlayerScript* pPlayerScript = new PlayerScript();
		//obj->AddComponent(pPlayerScript);

		mpPlayScene->AddGameObject(pGenaroChild, eLayerType::PLAYER);



		// Sprite
		GameObject* pSriteObj = new GameObject();
		Transform* pTransform = new Transform();
		pTransform->SetPosition(Vector3(10.0f, 0.0f, 20.0f));
		pSriteObj->AddComponent(pTransform);

		SpriteRenderer* pSpriteRenderer = new SpriteRenderer;

		pSpriteRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		Material* pSpriteMaterial = Resources::Find<Material>(SPRITE_MATERIAL_KEY);
		assert(pSpriteMaterial != nullptr);
		pSpriteMaterial->SetRenderingMode(eRenderingMode::TRANSPARENTT);
		pSpriteRenderer->SetMaterial(pSpriteMaterial);
		pSriteObj->AddComponent(pSpriteRenderer);
		mpPlayScene->AddGameObject(pSriteObj, eLayerType::PLAYER);


		// HPBar
		GameObject* pHPBarObj = new GameObject();
		Transform* pHPTransform = new Transform();
		pHPTransform->SetPosition(Vector3(-1.0f, 0.0f, 20.0f));
		pHPTransform->SetScale(Vector3(2.0f, 1.0f, 20.0f));
		pHPBarObj->AddComponent(pHPTransform);

		// SetMaterial
		Material* pHPBarMaterial = Resources::Find<Material>(UI_MATERIAL_KEY);
		//assert(pHPBarMaterial != nullptr);
		//Texture* pHPBarTexture = Resources::Find<Texture>(L"HPBarTexture");
		//assert(pHPBarTexture != nullptr);
		//pHPBarMaterial->SetTexture(pHPBarTexture);
		//pHPBarMaterial->SetRenderingMode(eRenderingMode::OPAQUEE);

		MeshRenderer* pHPBarMeshRenderer = new MeshRenderer();
		pHPBarMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pHPBarMeshRenderer->SetMaterial(pHPBarMaterial); 
		pHPBarObj->AddComponent(pHPBarMeshRenderer);

		//PlayerScript* pPlayerScript = new PlayerScript();
		//obj->AddComponent(pPlayerScript);

		mpPlayScene->AddGameObject(pHPBarObj, eLayerType::UI);


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