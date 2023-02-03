#include "jhSceneManager.h"
#include "jhScene.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMeshRenderer.h"
#include "jhRenderer.h"
#include "jhTexture.h"
#include "jhResources.h"

namespace jh
{

	Scene* SceneManager::mpPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mpPlayScene = new Scene();
		mpPlayScene->Initalize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		obj->AddComponent(tr);
		MeshRenderer* meshRenderer = new MeshRenderer;
		meshRenderer->SetShader(Resources::Find<Shader>(L"RectShader"));
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		obj->AddComponent(meshRenderer);
		
		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"Gennaro.bmp");
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
}