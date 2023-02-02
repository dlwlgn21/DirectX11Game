#include "jhGameObject.h"
#include "jhComponent.h"

namespace jh
{
	GameObject::GameObject()
		: meState(eState::ACTIVE)
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
		mComponents.resize(mComponents.capacity());
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr) 
				{ continue; }
			pComponent->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
			{
				continue;
			}
			pComponent->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
			{
				continue;
			}
			pComponent->FixedUpdate();
		}
	}
	void GameObject::Render()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
			{
				continue;
			}
			pComponent->Render();
		}
	}

	void GameObject::AddComponent(Component* pComponent)
	{
		assert(pComponent != nullptr);
		assert(mComponents[pComponent->GetOrder()] == nullptr);
		mComponents[pComponent->GetOrder()] = pComponent;
		mComponents[pComponent->GetOrder()]->SetOwner(this);
	}
}