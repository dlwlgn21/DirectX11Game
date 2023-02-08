#include "jhMeshRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhMaterial.h"

namespace jh
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MESH_RENDERER)
		, mpMesh(nullptr)
		, mpMaterial(nullptr)
	{
	}
	MeshRenderer::~MeshRenderer()
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
		Transform* pTrasform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTrasform != nullptr);
		pTrasform->WriteContantBufferAtGPUAndSetConstantBufferAtShader();
		assert(mpMaterial != nullptr);
		assert(mpMesh != nullptr);

		mpMaterial->BindConstantBufferAndShader();
		mpMesh->SetVertexAndIndexBufferAtIA();

		mpMesh->Render();
	}
}