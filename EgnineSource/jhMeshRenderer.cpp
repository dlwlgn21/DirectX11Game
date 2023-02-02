#include "jhMeshRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhShader.h"


namespace jh
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MESH_RENDERER)
		, mpMesh(nullptr)
		, mpShader(nullptr)
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
		assert(mpShader != nullptr);
		assert(mpMesh != nullptr);

		mpShader->SetPrimitiveTopologyAndIASetVertexAndPixelShader();
		mpMesh->SetVertexAndIndexBufferAtIA();

		mpMesh->Render();
	}
}