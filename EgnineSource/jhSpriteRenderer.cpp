#include "jhSpriteRenderer.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhAnimator.h"

namespace jh
{
	SpriteRenderer::SpriteRenderer()
		: RendererComponent(eComponentType::SPRITE_RENDERER)
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
		Transform* pTrasform = static_cast<Transform*>(GetOwner()->GetTransform());
		assert(pTrasform != nullptr);
		pTrasform->WriteContantBufferAtGPUAndSetConstantBufferAtShader();
		assert(mpMaterial != nullptr);
		assert(mpMesh != nullptr);

		mpMaterial->BindConstantBufferAndShaderAndSetTextureSRVAtShader();
		mpMesh->SetVertexAndIndexBufferAtIA();

		Animator* pAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		if (pAnimator != nullptr)
		{
			pAnimator->BindAtShader();
		}

		mpMesh->Render();
		mpMaterial->Clear();
	}
}