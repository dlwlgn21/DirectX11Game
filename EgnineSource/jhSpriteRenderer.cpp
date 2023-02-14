#include "jhSpriteRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhMaterial.h"

namespace jh
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SPRITE_RENDERER)
		, mpMesh(nullptr)
		, mpMaterial(nullptr)
	{
	}


	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::FixedUpdate()
	{
	}
	void SpriteRenderer::Render()
	{
		Transform* pTrasform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
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