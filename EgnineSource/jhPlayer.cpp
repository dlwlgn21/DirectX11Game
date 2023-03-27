#include "jhPlayer.h"
#include "jhSpriteRenderer.h"
#include "jhResources.h"
#include "jhPlayerScript.h"
#include "jhCollider2D.h"
#include "jhAnimator.h"
#include "jhTexture.h"

namespace jh
{
	Player::Player()
		: GameObject()
	{
		SpriteRenderer* pPlayerSpriteRenderer = new SpriteRenderer();
		pPlayerSpriteRenderer->SetMesh(Resources::Find<Mesh>(RECT_MESH_KEY));
		pPlayerSpriteRenderer->SetMaterial(Resources::Find<Material>(PLAYER_MATERIAL_KEY));
		this->AddComponent(pPlayerSpriteRenderer);
		PlayerScript* pPlayerScript = new PlayerScript();
		this->AddComponent(pPlayerScript);
		this->SetName(L"Player");
		Collider2D* pCollider2D = new Collider2D();
		pCollider2D->SetType(eColliderType::CIRCLE);
		pCollider2D->SetRadius(1.0f);
		this->GetTransform()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
		this->AddComponent(pCollider2D);

		Vector2 animSize(48.0f, 32.0f);
		Vector2 offset(0.015f, 0.0f);
		float height = 32.0f;
		Animator* pPlayerAnimator = new Animator();
		pPlayerAnimator->Create(
			L"PlayerIdle",
			Resources::Find<Texture>(renderer::PLAYER_TEXTURE_KEY),
			Vector2::Zero,
			animSize,
			offset,
			4,
			0.15f,
			100
		);
		pPlayerAnimator->Create(
			L"PlayerMove",
			Resources::Find<Texture>(renderer::PLAYER_TEXTURE_KEY),
			Vector2(0.0f, height * 4),
			animSize,
			offset,
			9,
			0.15f,
			100
		);
		pPlayerAnimator->Create(
			L"PlayerLeftPunch",
			Resources::Find<Texture>(renderer::PLAYER_TEXTURE_KEY),
			Vector2(0.0f, height * 12),
			animSize,
			offset,
			6,
			0.1f,
			100
		);
		pPlayerAnimator->Create(
			L"PlayerRightPunch",
			Resources::Find<Texture>(renderer::PLAYER_TEXTURE_KEY),
			Vector2(0.0f, height * 13),
			animSize,
			offset,
			5,
			0.1f,
			100
		);
		this->AddComponent(pPlayerAnimator);
		pPlayerAnimator->PlayAnimation(L"PlayerIdle", true);
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
}