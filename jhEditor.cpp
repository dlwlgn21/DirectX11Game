#include "jhEditor.h"
#include "EgnineSource/jhMesh.h"
#include "EgnineSource/jhResources.h"
#include "EgnineSource/jhRenderer.h"
#include "EgnineSource/jhMaterial.h"
#include "EgnineSource/jhTransform.h"
#include "EgnineSource/jhMeshRenderer.h"

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
		Mesh* pRectMesh = Resources::Find<Mesh>(renderer::RECT_MESH_KEY);
		Material* pDebugMaterial = Resources::Find<Material>(renderer::DEBUG_MATERIAL_KEY);
		mDebugObjects[static_cast<UINT>(eColliderType::RECT)] = new DebugObject();
		MeshRenderer* pRectMeshRenderer = new MeshRenderer();
		pRectMeshRenderer->SetMesh(pRectMesh);
		pRectMeshRenderer->SetMaterial(pDebugMaterial);
		mDebugObjects[static_cast<UINT>(eColliderType::RECT)]->AddComponent(pRectMeshRenderer);

		// CIRCLE
		Mesh* pCircleMesh = Resources::Find<Mesh>(renderer::CIRCLE_MESH_KEY);
		mDebugObjects[static_cast<UINT>(eColliderType::CIRCLE)] = new DebugObject();
		MeshRenderer* pCircleMeshRenderer = new MeshRenderer();
		pCircleMeshRenderer->SetMesh(pCircleMesh);
		pCircleMeshRenderer->SetMaterial(pDebugMaterial);
		mDebugObjects[static_cast<UINT>(eColliderType::CIRCLE)]->AddComponent(pCircleMeshRenderer);

	}
	void Editor::Update()
	{
	}
	void Editor::FixedUpdate()
	{
	}
	void Editor::Render()
	{
	}
	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		//DebugObject* pDebugObject = 
	}
	void Editor::Destroy()
	{
	}
	void Editor::Release()
	{
		/*
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;
		*/
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