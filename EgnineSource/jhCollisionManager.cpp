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
		colliderID.Left = static_cast<UINT32>(pLeftCollider->GetColliderID());
		colliderID.Right = static_cast<UINT32>(pRightCollider->GetColliderID());

		// 이젠 충돌 정보를 검색.

		auto findResIter = mCollisionMap.find(colliderID.Id);
		// ColliderID를 검색해서 없다면 충돌하지 않은 것.
		// 충돌정보를 생성해줌.
		if (findResIter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.Id, false));
			findResIter = mCollisionMap.find(colliderID.Id);
		}

		// 생성한 충돌정보 바탕으로 충돌체크 시작.
		if (Intersect(pLeftCollider, pRightCollider))
		{

			// 충돌 중이지 않은 상태 Enter
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
			// 이미 충돌 중인 상태 Stay
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
		else // 아예 충돌하지 않은 상태
		{
			// 막 빠져 나온 상태 Exit
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

				// 빠져나왔으니까 충돌중이 아님. 빠져나온 상태 업데이트.
				findResIter->second = false;
			}
		}


	}

	bool CollisionManager::Intersect(Collider2D* pLeftCollider, Collider2D* pRightCollider)
	{
		// RECT
		// 0 --- 1
		// |     |
		// 3 --- 2
		static const int RECT_VECTEX_COUNT = 4;

		static const Vector3 ARR_LOCAL_POS[RECT_VECTEX_COUNT] =
		{
			Vector3{-0.5f, 0.5f, 0.0f},
			Vector3{0.5f, 0.5f, 0.0f},
			Vector3{0.5f, -0.5f, 0.0f},
			Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* pLeftTransform = pLeftCollider->GetOwner()->GetTransform();
		Transform* pRightTransform = pRightCollider->GetOwner()->GetTransform();

		const Matrix& leftWorldMat = pLeftTransform->GetWorldMatrix();
		const Matrix& rightWorldMat = pRightTransform->GetWorldMatrix();


		// 분리축 벡터.
		Vector3 axisVectors[RECT_VECTEX_COUNT] = {};
		axisVectors[0] = Vector3::Transform(ARR_LOCAL_POS[1], leftWorldMat)	 -	Vector3::Transform(ARR_LOCAL_POS[0], leftWorldMat);
		axisVectors[1] = Vector3::Transform(ARR_LOCAL_POS[3], leftWorldMat)	 -	Vector3::Transform(ARR_LOCAL_POS[0], leftWorldMat);
		axisVectors[2] = Vector3::Transform(ARR_LOCAL_POS[1], rightWorldMat) -	Vector3::Transform(ARR_LOCAL_POS[0], rightWorldMat);
		axisVectors[3] = Vector3::Transform(ARR_LOCAL_POS[3], rightWorldMat) -	Vector3::Transform(ARR_LOCAL_POS[0], rightWorldMat);
		
		for (int i = 0; i < RECT_VECTEX_COUNT; ++i)
		{
			axisVectors[i].z = 0.0f;
		}
		Vector3 centerDistanceVector = pLeftCollider->GetPosition() - pRightCollider->GetPosition();
		centerDistanceVector.z = 0.0f;

		Vector3 centerDir = centerDistanceVector;

		// 투영 시킴
		for (int i = 0; i < RECT_VECTEX_COUNT; ++i)
		{
			Vector3 axisDirectionVector = axisVectors[i];
			axisDirectionVector.Normalize();

			float projectionDistance = 0.0f;
			for (int j = 0; j < RECT_VECTEX_COUNT; ++j)
			{
				projectionDistance += fabsf(axisVectors[j].Dot(axisDirectionVector) / 2.0f);
			}

			if (projectionDistance < fabsf(centerDir.Dot(axisDirectionVector)))
			{
				return false;
			}
		}

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