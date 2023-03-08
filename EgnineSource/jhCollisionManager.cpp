#include "jhCollisionManager.h"
#include "jhSceneManager.h"
#include "jhGameObject.h"

namespace jh
{
	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* pCurrScene = SceneManager::GetInatance().GetCurrentScene();
		assert(pCurrScene != nullptr);

		for (UINT row = 0; row < static_cast<UINT>(eLayerType::COUNT); ++row)
		{
			for (UINT col = 0; col < static_cast<UINT>(eLayerType::COUNT); ++col)
			{
				if (mLayerCollisionMatrix[row][col])
				{
					CheckLayerCollision(pCurrScene, static_cast<eLayerType>(row), static_cast<eLayerType>(col));
				}
			}
		}
	}
	void CollisionManager::CheckLayerCollision(Scene* pScene, const eLayerType eLeftLayer, const eLayerType eRightLayer)
	{
		const std::vector<GameObject*>& leftLayerGameObjects = pScene->GetAllGameObjectsFromLayer(eLeftLayer);
		const std::vector<GameObject*>& rightLayerGameObjects = pScene->GetAllGameObjectsFromLayer(eRightLayer);

		for (auto* pLeftObject : leftLayerGameObjects)
		{
			if (pLeftObject->GetState() != GameObject::eState::ACTIVE)
				{continue;}
			Collider2D* pLeftCollider = static_cast<Collider2D*>(pLeftObject->GetComponentOrNull(eComponentType::COLLIDER));
			if (pLeftCollider == nullptr)
				{continue;}
			for (auto* pRightObject : rightLayerGameObjects)
			{
				if (pRightObject->GetState() != GameObject::eState::ACTIVE)
					{continue;}
				Collider2D* pRightCollider = static_cast<Collider2D*>(pRightObject->GetComponentOrNull(eComponentType::COLLIDER));
				if (pRightObject->GetComponentOrNull(eComponentType::COLLIDER) == nullptr)
					{continue;}
				if (pLeftObject == pRightObject)
					{continue;}

				CheckValidColliderCollision(pLeftCollider, pRightCollider);
			}
		}
	}
	void CollisionManager::CheckValidColliderCollision(Collider2D* pLeftCollider, Collider2D* pRightCollider)
	{
		ColliderID colliderID;
		colliderID.Left = reinterpret_cast<UINT32>(pLeftCollider);
		colliderID.Right = reinterpret_cast<UINT32>(pRightCollider);

		// ���� �浹 ������ �˻�.

		auto findResIter = mCollisionMap.find(colliderID.Id);
		// ColliderID�� �˻��ؼ� ���ٸ� �浹���� ���� ��.
		// �浹������ ��������.
		if (findResIter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.Id, false));
			findResIter = mCollisionMap.find(colliderID.Id);
		}

		// ������ �浹���� �������� �浹üũ ����.
		if (Intersect(pLeftCollider, pRightCollider))
		{

			// �浹 ������ ���� ���� Enter
			if (findResIter->second == false)
			{
				if (pLeftCollider->GetIsUsePhysics())
					{pLeftCollider->OnCollisionEnter(pRightCollider);}
				else
					{pLeftCollider->OnTriggerEnter(pRightCollider);}

				if (pRightCollider->GetIsUsePhysics())
					{pRightCollider->OnCollisionEnter(pLeftCollider);}
				else
					{pRightCollider->OnTriggerEnter(pLeftCollider);}
				findResIter->second = true;
			}
			// �̹� �浹 ���� ���� Stay
			else
			{
				if (pLeftCollider->GetIsUsePhysics())
					{pLeftCollider->OnCollisionStay(pRightCollider);}
				else
					{pLeftCollider->OnTriggerStay(pRightCollider);}

				if (pRightCollider->GetIsUsePhysics())
					{pRightCollider->OnCollisionStay(pLeftCollider);}
				else
					{pRightCollider->OnTriggerStay(pLeftCollider);}
			}
		}
		else // �ƿ� �浹���� ���� ����
		{
			// �� ���� ���� ���� Exit
			if (findResIter->second == true)
			{
				if (pLeftCollider->GetIsUsePhysics())
					{pLeftCollider->OnCollisionExit(pRightCollider);}
				else
					{pLeftCollider->OnTriggerExit(pRightCollider);}

				if (pRightCollider->GetIsUsePhysics())
					{pRightCollider->OnCollisionExit(pLeftCollider);}
				else
					{pRightCollider->OnTriggerExit(pLeftCollider);}

				// �����������ϱ� �浹���� �ƴ�. �������� ���� ������Ʈ.
				findResIter->second = false;
			}
		}


	}

	bool CollisionManager::Intersect(Collider2D* pLeftCollider, Collider2D* pRightCollider)
	{
		return true;
	}

	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}


	void CollisionManager::CollisionLayerCheck(const eLayerType eLeftLayer, const eLayerType eRightLayer, bool bIsEnable)
	{
		UINT row = 0;
		UINT col = 0;
		UINT leftNum = static_cast<UINT>(eLeftLayer);
		UINT rightNum = static_cast<UINT>(eRightLayer);
		if (leftNum <= rightNum)
		{
			row = leftNum;
			col = rightNum;
		}
		else
		{
			row = rightNum;
			col = leftNum;
		}
		mLayerCollisionMatrix[row][col] = bIsEnable;
	}

}