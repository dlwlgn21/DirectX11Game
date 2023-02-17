#include "jhGameObject.h"
#include "jhComponent.h"
#include "jhScript.h"

namespace jh
{
	GameObject::GameObject()
		: meState(eState::ACTIVE)
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
		mComponents.resize(mComponents.capacity());
		mScripts.reserve(4);
		//mScripts.resize(mScripts.capacity());
	}


	GameObject::~GameObject()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
			{
				continue;
			}
			delete pComponent;
		}

		for (auto* pScript : mScripts)
		{
			if (pScript == nullptr)
			{
				continue;
			}
			delete pScript;
		}
		mComponents.clear();
		mScripts.clear();
	}

	void GameObject::Initialize()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr) 
				{continue;}
			pComponent->Initialize();
		}

		for (auto* pScript : mScripts)
		{
			if (pScript == nullptr)
				{continue;}
			pScript->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
				{continue;}
			pComponent->Update();
		}

		for (auto* pScript : mScripts)
		{
			if (pScript == nullptr)
				{continue;}
			pScript->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
				{continue;}
			pComponent->FixedUpdate();
		}

		for (auto* pScript : mScripts)
		{
			if (pScript == nullptr)
				{continue;}
			pScript->FixedUpdate();
		}
	}
	void GameObject::Render()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
				{continue;}
			pComponent->Render();
		}
	}

	void GameObject::AddComponent(Component* pComponent)
	{
		assert(pComponent != nullptr);
		assert(mComponents[pComponent->GetOrder()] == nullptr);
		if (pComponent->getType() != eComponentType::SCRIPT) 
		{
			mComponents[pComponent->GetOrder()] = pComponent;
			mComponents[pComponent->GetOrder()]->SetOwner(this);
		}
		else 
		{
			mScripts.push_back(static_cast<Script*>(pComponent));
			pComponent->SetOwner(this);
		}


	}
}