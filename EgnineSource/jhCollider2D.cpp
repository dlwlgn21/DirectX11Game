#include "jhCollider2D.h"
#include "jhGameObject.h"
#include "jhRenderer.h"


namespace jh
{
	Collider2D::Collider2D()
		: Component(eComponentType::COLLIDER)
		, meColliderType(eColliderType::NONE)
		, mpTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mbIsPhysicsTrigger(false)
	{
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
		meshAttribute.Radius = mSize.x;
		meshAttribute.Rotation = rot;
		meshAttribute.Scale = scale; 
		meshAttribute.EColliderType = meColliderType;
		renderer::debugMeshs.push_back(meshAttribute);
	}
	void Collider2D::Render()
	{
	}
}