#pragma once
#include "jhScene.h"
#include "jhLayer.h"
#include "jhGameObject.h"
#include "jhSceneManager.h"
#include "jhTransform.h"
#include "..\jhEditorObject.h"

namespace jh::object
{
	static GameObject* Instantiate(eLayerType eLayer)
	{
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		layer.AddGameObject(pGameObj, eLayer);
		return pGameObj;
	}

	static EditorObject* InstantiateEditorObject(eLayerType eLayer)
	{
		EditorObject* pGameObj = new EditorObject();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		layer.AddGameObject(pGameObj, eLayer);
		return pGameObj;
	}
	template<typename T>
	static T* Instantiate(eLayerType eLayer)
	{
		T* pGameObj = new T();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		layer.AddGameObject(pGameObj, eLayer);
		return pGameObj;
	}

	static GameObject* Instantiate(eLayerType eLayer, Scene* pScene)
	{
		GameObject* pGameObj = new GameObject();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		layer.AddGameObject(pGameObj, eLayer);
		return pGameObj;
	}
	static GameObject* Instantiate(eLayerType eLayer, Transform* pTransformParent)
	{
		assert(pTransformParent != nullptr);
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetParent(pTransformParent);
		layer.AddGameObject(pGameObj, eLayer);

		return pGameObj;
	}

	static GameObject* Instantiate(eLayerType eLayer, Vector3 position, Vector3 rotation)
	{
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetPosition(position);
		pTransform->SetRotation(rotation);
		layer.AddGameObject(pGameObj, eLayer);

		return pGameObj;
	}

	template<typename T>
	static T* Instantiate(eLayerType eLayer, Vector3 position, Vector3 rotation)
	{
		T* pGameObj = new T();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetPosition(position);
		pTransform->SetRotation(rotation);
		layer.AddGameObject(pGameObj, eLayer);

		return pGameObj;
	}
	static GameObject* Instantiate(eLayerType eLayer, Vector3 position, Vector3 rotation, Transform* pTransformParent)
	{
		assert(pTransformParent != nullptr);
		GameObject* pGameObj = new GameObject();
		Scene* pScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pScene != nullptr);
		Layer& layer = pScene->GetLayer(eLayer);

		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);
		pTransform->SetPosition(position);
		pTransform->SetRotation(rotation);
		pTransform->SetParent(pTransformParent);

		layer.AddGameObject(pGameObj, eLayer);

		return pGameObj;
	}

	static void Destroy(GameObject* pGameObj)
	{
		assert(pGameObj != nullptr);
		pGameObj->SetDead();
	}

	static void DontDestroyOnLoad(GameObject* pGameObj)
	{
		assert(pGameObj != nullptr);
		pGameObj->DontDestroy();
	}
}
