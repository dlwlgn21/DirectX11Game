#include "jhSceneManager.h"
#include "jhScene.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhTexture.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhPlayerScript.h"


namespace jh
{

	Scene* SceneManager::mpPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mpPlayScene = new Scene();
		mpPlayScene->Initalize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.3f, 0.3f, 0.0f));
		obj->AddComponent(tr);
		MeshRenderer* pMeshRenderer = new MeshRenderer;
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		Material* pMaterial = Resources::Find<Material>(L"RectMaterial");
		assert(pMaterial != nullptr);
		Vector2 passVector2(1.0f, 1.0f);
		pMaterial->SetDataAtConstantBuffer(eGPUPrameterType::VECTOR2, &passVector2);
		pMeshRenderer->SetMaterial(pMaterial);
		obj->AddComponent(pMeshRenderer);
		
		PlayerScript* pPlayerScript = new PlayerScript();
		obj->AddComponent(pPlayerScript);

		Texture* texture = Resources::Load<Texture>(L"GennaroTexture", L"Gennaro.bmp");
		assert(texture != nullptr);
		texture->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0);
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
	void SceneManager::Release()
	{
		mpPlayScene->Release();
		delete mpPlayScene;
	}
}