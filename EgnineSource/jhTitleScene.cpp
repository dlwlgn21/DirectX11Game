#include "jhTitleScene.h"
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
#include "jhCollider2D.h"
#include "jhPlayer.h"
#include "jhMonster.h"
#include "jhCollisionManager.h"
#include "jhAnimator.h"


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
		//GameObject* pBGObject = jh::object::Instantiate(eLayerType::NONE, Vector3(15.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, 0.0f));
		//MeshRenderer* pBGMeshRender = new MeshRenderer();
		//pBGMeshRender->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		//pBGMeshRender->SetMaterial(Resources::Find<Material>(TITLE_BACKGROUND_MATERIAL_KEY));
		//pBGObject->AddComponent(pBGMeshRender);

		// Player
		Player* pPlayerObj = jh::object::Instantiate<Player>(eLayerType::PLAYER, Vector3(-3.0f, 0.0f, 20.0f), Vector3(0.0f, 0.0f, 0.0f));
		SpriteRenderer* pPlayerSpriteRenderer = new SpriteRenderer();
		pPlayerSpriteRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pPlayerSpriteRenderer->SetMaterial(Resources::Find<Material>(PLAYER_MATERIAL_KEY));
		pPlayerObj->AddComponent(pPlayerSpriteRenderer);
		PlayerScript* pPlayerScript = new PlayerScript();
		pPlayerObj->AddComponent(pPlayerScript);
		pPlayerObj->SetName(L"Player");
		Collider2D* pCollider2D = new Collider2D();
		pCollider2D->SetType(eColliderType::CIRCLE);
		pCollider2D->SetRadius(1.0f);
		pPlayerObj->AddComponent(pCollider2D);
		//object::DontDestroyOnLoad(pPlayerObj);
		pCollider2D->SetSize(Vector2(1.5f, 1.5f));

		//Animator* pPlayerAnimator = new Animator();
		//pPlayerAnimator->Create(
		//	L"ZeldaIdle",
		//	Resources::Find<Texture>(renderer::ZELDA_TEXTURE_KEY),
		//	Vector2::Zero,
		//	Vector2(120.f, 130.0f),
		//	Vector2::Zero,
		//	10,
		//	3,
		//	0.1f
		//);
		//pPlayerObj->AddComponent(pPlayerAnimator);
		//pPlayerAnimator->PlayAnimation(L"ZeldaIdle", true);


		// Monster
		Monster* pMonsterObjTwo = jh::object::Instantiate<Monster>(eLayerType::MONSTER, Vector3(5.0f, 0.0f, 20.0f), Vector3(0.0f, 0.0f, 0.0f));
		//pMonsterObjTwo->GetTransform()->SetRotation(Vector3(pMonsterObjTwo->GetTransform()->GetRotation().x, pMonsterObjTwo->GetTransform()->GetRotation().y, XM_PIDIV2 / 2.0f));
		SpriteRenderer* pMonsterSpriteRenderer = new SpriteRenderer();
		pMonsterSpriteRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		Material* pMaterial = Resources::Find<Material>(MONSTER_MATERIAL_KEY);
		pMaterial->SetShader(Resources::Find<Shader>(renderer::CHARACTER_SHADER_KEY));
		pMonsterSpriteRenderer->SetMaterial(Resources::Find<Material>(MONSTER_MATERIAL_KEY));
		pMonsterObjTwo->AddComponent(pMonsterSpriteRenderer);

		pMonsterObjTwo->SetName(L"Monster");
		Collider2D* pCollider2DTwo = new Collider2D();
		pCollider2DTwo->SetType(eColliderType::CIRCLE);
		pCollider2DTwo->SetRadius(1.0f);
		pMonsterObjTwo->AddComponent(pCollider2DTwo);
		CollisionManager::GetInstance().CollisionLayerCheck(eLayerType::PLAYER, eLayerType::MONSTER, true);
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