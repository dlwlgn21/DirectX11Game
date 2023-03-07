#include "jhTitleScene.h"
#include "jhInput.h"
#include "jhSceneManager.h"
#include "jhCamera.h"
#include "jhCameraScript.h"
#include "jhObject.h"


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
		GameObject* pCameraObj = object::Instantiate(eLayerType::CAMERA, this);
		Camera* pCameraComponent = new Camera();
		pCameraObj->AddComponent(pCameraComponent);
		pCameraComponent->TurnLayerMasks(eLayerType::UI, false);
		pCameraObj->AddComponent(new CameraScript());
		pCameraObj->SetName(L"Title Scene Main Camera");
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