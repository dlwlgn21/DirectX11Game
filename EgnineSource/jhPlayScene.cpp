#include "jhPlayScene.h"
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
#include "jhGridScript.h"
#include "jhObject.h"
#include "jhFadeOutScript.h"
#include "jhFadeInScript.h"
#include "jhInput.h"

namespace jh
{
	PlayScene::PlayScene()
		: Scene(eSceneType::PLAY)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initalize()
	{
		// Grid Object
		GameObject* pGridObj = jh::object::Instantiate(eLayerType::GRID);
		Material* pGridMaterial = Resources::Find<Material>(GRID_MATERIAL_KEY);
		pGridMaterial->SetTexture(Resources::Find<Texture>(DEFAULT_TEXTURE_KEY));
		MeshRenderer* pGridMeshRenderer = new MeshRenderer();
		pGridMeshRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pGridMeshRenderer->SetMaterial(pGridMaterial);
		pGridObj->AddComponent(pGridMeshRenderer);
		pGridObj->AddComponent(new GridScript());

		// Camera Game Obj
		GameObject* pCameraObj = jh::object::Instantiate(eLayerType::CAMERA);
		Camera* pCameraComponent = new Camera();
		//pCameraComponent->registerCameraAtRenderer();
		pCameraObj->AddComponent(pCameraComponent);
		pCameraComponent->TurnLayerMasks(eLayerType::UI, false);
		pCameraObj->AddComponent(new CameraScript());
		pCameraComponent->SetName(L"Main Camera");

		//Camera UI Game Obj
		GameObject* pCameraUIObj = jh::object::Instantiate(eLayerType::CAMERA);
		Camera* pCameraUIComponent = new Camera();
		pCameraUIComponent->SetProjectionType(Camera::eProjectionType::ORTHOGRAPHIC);
		pCameraUIComponent->DisableAllLayerMasks();
		pCameraUIComponent->TurnLayerMasks(eLayerType::UI, true);
		pCameraUIObj->AddComponent(pCameraUIComponent);
		pCameraUIComponent->SetName(L"UI Camera");

		// Gennaro
		GameObject* pGenaroObj = jh::object::Instantiate(eLayerType::PLAYER, Vector3(-3.0f, 0.0f, 20.0f), Vector3(0.0f, 0.0f, XM_PIDIV2));
		MeshRenderer* pMeshRenderer = new MeshRenderer();
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pMeshRenderer->SetMaterial(Resources::Find<Material>(DEFAULT_MATERIAL_KEY));
		pGenaroObj->AddComponent(pMeshRenderer);
		PlayerScript* pPlayerScript = new PlayerScript();
		pGenaroObj->AddComponent(pPlayerScript);
		pGenaroObj->SetName(L"Genaro");
		object::DontDestroyOnLoad(pGenaroObj);


		// Gennaro Child
		GameObject* pGenaroChild = jh::object::Instantiate(eLayerType::PLAYER, pGenaroObj->GetTransform());
		Transform* pChildTransform = pGenaroChild->GetTransform();
		pChildTransform->SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
		MeshRenderer* pGenaroChildMeshRenderer = new MeshRenderer();
		pGenaroChildMeshRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pGenaroChildMeshRenderer->SetMaterial(Resources::Find<Material>(DEFAULT_MATERIAL_KEY));
		pGenaroChild->AddComponent(pGenaroChildMeshRenderer);


		// Sprite
		GameObject* pSriteObj = jh::object::Instantiate(eLayerType::PLAYER, Vector3(10.0f, 0.0f, 20.0f), Vector3::Zero);

		SpriteRenderer* pSpriteRenderer = new SpriteRenderer;
		pSpriteRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		Material* pSpriteMaterial = Resources::Find<Material>(SPRITE_MATERIAL_KEY);
		assert(pSpriteMaterial != nullptr);
		pSpriteMaterial->SetRenderingMode(eRenderingMode::TRANSPARENTT);
		pSpriteRenderer->SetMaterial(pSpriteMaterial);
		pSriteObj->AddComponent(pSpriteRenderer);


		// HPBar
		GameObject* pHPBarObj = jh::object::Instantiate(eLayerType::UI, Vector3(-1.0f, 0.0f, 20.0f), Vector3::Zero);
		Transform* pHPTransform = pHPBarObj->GetTransform();
		pHPTransform->SetScale(Vector3(2.0f, 1.0f, 20.0f));

		// SetMaterial
		Material* pHPBarMaterial = Resources::Find<Material>(UI_MATERIAL_KEY);
		MeshRenderer* pHPBarMeshRenderer = new MeshRenderer();
		pHPBarMeshRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pHPBarMeshRenderer->SetMaterial(pHPBarMaterial);
		pHPBarObj->AddComponent(pHPBarMeshRenderer);


		// Fadeout
		GameObject* pFadeOut = jh::object::Instantiate(eLayerType::PLAYER);
		Material* pFadeOutMaterial = Resources::Find<Material>(FADE_OUT_MATERIAL_KEY);
		MeshRenderer* pFadeOutRenderer = new MeshRenderer();
		//FadeoutScript* pFadeoutScript = new FadeoutScript();
		FadeinScript* pFadeInScript = new FadeinScript();
		pFadeOutRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pFadeOutRenderer->SetMaterial(pFadeOutMaterial);
		pFadeOut->AddComponent(pFadeOutRenderer);
		pFadeOut->AddComponent(pFadeInScript);
		Scene::Initalize();

	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::DOWN)
		{
			SceneManager::GetInatance().LoadScene(eSceneType::TITLE);
		}
		Scene::Update();
	}
	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}