#include "jhGameObject.h"

namespace jh
{
	GameObject::GameObject()
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Tick()
	{
	}
	void GameObject::FixedUpdate()
	{
	}
	void GameObject::Render()
	{
	}
	void GameObject::AddComponent(Component* pComponent)
	{
	}
}