#include "jhEditor.h"
#include "EgnineSource/jhMesh.h"
#include "EgnineSource/jhResources.h"
#include "EgnineSource/jhRenderer.h"
#include "EgnineSource/jhMaterial.h"
#include "EgnineSource/jhTransform.h"
#include "EgnineSource/jhMeshRenderer.h"
#include "EgnineSource/jhObject.h"
#include "EgnineSource/jhGridScript.h"
#include "jhEditorObject.h"
#include "EgnineSource/jhCamera.h"
#include "EgnineSource/jhCollider2D.h"
#include "EgnineSource/jhSceneManager.h"


namespace jh
{
	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Editor::Initialize()
	{
		// 충돌체의 종류 갯수만큼만 있으면 됩니당.
		mDebugObjects.reserve(static_cast<UINT>(eColliderType::COUNT));
		mDebugObjects.resize(mDebugObjects.capacity());

		// RECT
		Mesh* pRectDebugMesh = Resources::Find<Mesh>(renderer::RECT_DEBUG_MESH_KEY);
		Material* pDebugMaterial = Resources::Find<Material>(renderer::DEBUG_MATERIAL_KEY);

		mDebugObjects[static_cast<UINT>(eColliderType::RECT)] = new DebugObject();
		MeshRenderer* pRectMeshRenderer = new MeshRenderer();
		pRectMeshRenderer->SetMesh(pRectDebugMesh);
		pRectMeshRenderer->SetMaterial(pDebugMaterial);
		mDebugObjects[static_cast<UINT>(eColliderType::RECT)]->AddComponent(pRectMeshRenderer);

		// CIRCLE
		Mesh* pCircleMesh = Resources::Find<Mesh>(renderer::CIRCLE_DEBUG_MESH_KEY);
		mDebugObjects[static_cast<UINT>(eColliderType::CIRCLE)] = new DebugObject();
		MeshRenderer* pCircleMeshRenderer = new MeshRenderer();
		pCircleMeshRenderer->SetMesh(pCircleMesh);
		pCircleMeshRenderer->SetMaterial(pDebugMaterial);
		mDebugObjects[static_cast<UINT>(eColliderType::CIRCLE)]->AddComponent(pCircleMeshRenderer);


		// Grid Object
		EditorObject* pGridObj = new EditorObject();
		Material* pGridMaterial = Resources::Find<Material>(renderer::GRID_MATERIAL_KEY);
		MeshRenderer* pGridMeshRenderer = new MeshRenderer();
		pGridMeshRenderer->SetMesh(Resources::Find<Mesh>(renderer::RECT_MESH_KEY));
		pGridMeshRenderer->SetMaterial(pGridMaterial);
		pGridObj->AddComponent(pGridMeshRenderer);
		GridScript* pGridScript = new GridScript();
		pGridScript->SetCamera(renderer::pMainCamera);
		pGridObj->AddComponent(pGridScript);
		mEditorObjects.push_back(pGridObj);
	}
	void Editor::Update()
	{
		for (auto* pEditorObject : mEditorObjects)
		{
			if (pEditorObject != nullptr)
			{
				pEditorObject->Update();
			}
		}

		//for (auto* pDebugObject : mDebugObjects)
		//{
		//	if (pDebugObject != nullptr)
		//	{
		//		pDebugObject->Update();
		//	}
		//}
	}
	void Editor::FixedUpdate()
	{
		for (auto* pEditorObject : mEditorObjects)
		{
			if (pEditorObject != nullptr)
			{
				pEditorObject->FixedUpdate();
			}
		}
		//for (auto* pDebugObject : mDebugObjects)
		//{
		//	if (pDebugObject != nullptr)
		//	{
		//		pDebugObject->FixedUpdate();
		//	}
		//}
	}
	void Editor::Render()
	{
		for (auto* pEditorObject : mEditorObjects)
		{
			if (pEditorObject != nullptr)
			{
				pEditorObject->Render();
			}
		}

		//for (auto* pDebugObject : mDebugObjects)
		//{
		//	if (pDebugObject != nullptr)
		//	{
		//		pDebugObject->Render();
		//	}
		//}
		for (auto& debugMesh : renderer::debugMeshs)
		{
			DebugRender(debugMesh);
		}
		renderer::debugMeshs.clear();
	}
	void Editor::DebugRender(const graphics::DebugMesh& mesh)
	{
		DebugObject* pDebugObject = mDebugObjects[static_cast<UINT>(mesh.EColliderType)];
		Transform* pTr = pDebugObject->GetTransform();
		pTr->SetPosition(mesh.Position);
		pTr->SetRotation(mesh.Rotation);

		if (mesh.EColliderType == eColliderType::RECT)
		{
			pTr->SetScale(mesh.Scale);
		}
		else
		{
			pTr->SetScale(Vector3(mesh.Radius));
		}

		Camera* pMainCamera = renderer::pMainCamera;
		assert(pMainCamera != nullptr);

		// 바뀐 값들 다시 행렬 세팅해주어야 하니까 다시 한번 FixedUpdate 호출함.
		pTr->FixedUpdate();		
		Camera::SetGPUViewMatrix(pMainCamera->GetViewMatrix());
		Camera::SetGPUProjectionMatrix(pMainCamera->GetProjectionMatrix());
		pDebugObject->Render();

	}
	void Editor::Destroy()
	{
	}
	void Editor::Release()
	{
		for (auto* pWidget : mWidgets)
		{
			if (pWidget == nullptr)
				{continue;}
			delete pWidget;
		}
		for (auto* pEditorObject : mEditorObjects)
		{
			if (pEditorObject == nullptr)
				{continue;}
			delete pEditorObject;
		}
		for (auto* pDebugObjects : mDebugObjects)
		{
			if (pDebugObjects == nullptr)
				{continue;}
			delete pDebugObjects;
		}
	}
}