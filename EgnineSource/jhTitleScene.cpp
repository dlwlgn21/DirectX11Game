#include "jhTitleScene.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhObject.h"
#include "jhMeshRenderer.h"
#include "jhResources.h"


namespace jh
{
	TitleScene::TitleScene()
		: Scene(eSceneType::TITLE)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
		// Camera Game Obj
		GameObject* pCameraObj = jh::object::Instantiate(eLayerType::CAMERA);
		Camera* pCameraComponent = new Camera();
		//pCameraComponent->registerCameraAtRenderer();
		pCameraObj->AddComponent(pCameraComponent);
		pCameraComponent->TurnLayerMasks(eLayerType::UI, false);
		pCameraObj->AddComponent(new CameraScript());
		pCameraComponent->SetName(L"Main Camera");
		renderer::pMainCamera = pCameraComponent;


		// BackGround
		GameObject* pBGObject = jh::object::Instantiate(eLayerType::NONE, Vector3(15.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, 0.0f));
		MeshRenderer* pBGMeshRender = new MeshRenderer();
		pBGMeshRender->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pBGMeshRender->SetMaterial(Resources::Find<Material>(TITLE_BACKGROUND_MATERIAL_KEY));
		pBGObject->AddComponent(pBGMeshRender);
		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::DOWN) 
		{
			SceneManager::GetInatance().LoadScene(eSceneType::PLAY);
		}
		Scene::Update(); 
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::Release()
	{
		Scene::Release();
	}
	void TitleScene::OnEnter()
	{


		Scene::OnEnter();
	}
	void TitleScene::OnExit()
	{
		Scene::OnExit();
	}
}