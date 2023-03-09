#include "jhCollider2D.h"
#include "jhGameObject.h"
#include "jhRenderer.h"
#include "jhScript.h"

namespace jh
{
	UINT Collider2D::sTotalColliderCount = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::COLLIDER)
		, meColliderType(eColliderType::NONE)
		, mpTransform(nullptr)
		, mRadius(0.0f)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mPosition(Vector3::Zero)
		, mbIsUsePhysics(false)
		, mUniqueColliderNumber(sTotalColliderCount)
	{
		++sTotalColliderCount;
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{ 
		//mpTransform = GetOwner()->GetTransform();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::FixedUpdate()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		Vector3 scale = mpTransform->GetScale();
		scale *= Vector3(mSize.x, mSize.y, 1.0f);
		Vector3 rot = mpTransform->GetRotation();

		Vector3 pos = mpTransform->GetPosition();
		Vector3 colliderPos = pos + Vector3(mCenter.x, mCenter.y, 0.0f);
		mPosition = colliderPos;

		Matrix scaleMat = Matrix::CreateScale(scale);
		Matrix rotMat;
		rotMat = Matrix::CreateRotationX(rot.x);
		rotMat *= Matrix::CreateRotationY(rot.y);
		rotMat *= Matrix::CreateRotationZ(rot.z);

		Matrix translationMat;
		translationMat.Translation(Vector3(colliderPos.x, colliderPos.y, colliderPos.z));

		Matrix worldMat = scaleMat * rotMat * translationMat;

		DebugMesh meshAttribute = {};
		meshAttribute.Position = Vector3(colliderPos.x, colliderPos.y, colliderPos.z);
		meshAttribute.Radius = mRadius;
		meshAttribute.Rotation = rot;
		meshAttribute.Scale = scale; 
		meshAttribute.EColliderType = meColliderType;
		renderer::debugMeshs.push_back(meshAttribute);
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnCollisionEnter(pOtherCollider);
			}
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnCollisionStay(pOtherCollider);
			}
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnCollisionExit(pOtherCollider);
			}
		}
	}
	void Collider2D::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnTriggerEnter(pOtherCollider);
			}
		}
	}
	void Collider2D::OnTriggerStay(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnTriggerStay(pOtherCollider);
			}
		}
	}
	void Collider2D::OnTriggerExit(Collider2D* pOtherCollider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			if (pScript != nullptr)
			{
				pScript->OnTriggerExit(pOtherCollider);
			}
		}
	}
}