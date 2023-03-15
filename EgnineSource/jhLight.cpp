#include "jhLight.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhRenderer.h"

namespace jh
{
	Light::Light()
		: Component(eComponentType::LIGHT)
	{
	}

	void Light::Initialize()
	{
	}

	void Light::Update()
	{
	}

	void Light::FixedUpdate()
	{
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);
		Vector3 position = pTransform->GetPosition();
		mLightAttribute.Position = Vector4(position.x, position.y, position.z, 1.0f);
		mLightAttribute.Direction = Vector4(pTransform->GetRight().x, pTransform->GetRight().y, pTransform->GetRight().z, 1.0f);
		renderer::lights.push_back(mLightAttribute);
	}

	void Light::Render()
	{
	}
}