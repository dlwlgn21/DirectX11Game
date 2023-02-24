#include "jhMeshRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhMaterial.h"

namespace jh
{
	MeshRenderer::MeshRenderer()
		: RendererComponent(eComponentType::MESH_RENDERER)
	{
	}

	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::FixedUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* pTrasform = GetOwner()->GetTransform();
		assert(pTrasform != nullptr);
		pTrasform->WriteContantBufferAtGPUAndSetConstantBufferAtShader();
		assert(mpMaterial != nullptr);
		assert(mpMesh != nullptr);

		mpMaterial->BindConstantBufferAndShaderAndSetTextureSRVAtShader();
		mpMesh->SetVertexAndIndexBufferAtIA();

		mpMesh->Render();
		mpMaterial->Clear();
	}
}