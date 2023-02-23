#pragma once
#include "jhScene.h"
#include "jhLayer.h"
#include "jhGameObject.h"
#include "jhSceneManager.h"
#include "jhTransform.h"

namespace jh::object
{
	GameObject* Instantiate(eLayerType eLayer)
	{
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		layer.AddGameObject(pGameObj);

		return pGameObj;
	}

	GameObject* Instantiate(eLayerType eLayer, Transform* pTransformParent)
	{
		assert(pTransformParent != nullptr);
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetParent(pTransformParent);
		layer.AddGameObject(pGameObj);

		return pGameObj;
	}

	GameObject* Instantiate(eLayerType eLayer, Vector3 position, Vector3 rotation)
	{
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetPosition(position);
		pTransform->SetRotation(rotation);
		layer.AddGameObject(pGameObj);

		return pGameObj;
	}

	GameObject* Instantiate(eLayerType eLayer, Vector3 position, Vector3 rotation, Transform* pTransformParent)
	{
		assert(pTransformParent != nullptr);
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetPosition(position);
		pTransform->SetRotation(rotation);
		pTransform->SetParent(pTransformParent);

		layer.AddGameObject(pGameObj);

		return pGameObj;
	}

	void Destroy(GameObject* pGameObj)
	{
		assert(pGameObj != nullptr);
		pGameObj->SetDead();
	}
}
