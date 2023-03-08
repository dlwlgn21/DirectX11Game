#pragma once
#include "Engine.h"
#include "jhCollider2D.h"


namespace jh
{

	union ColliderID
	{
		struct
		{
			UINT32 Left;
			UINT32 Right;
		};
		UINT64 Id;
	};
	class Scene;
	class CollisionManager final
	{
	public:
		static CollisionManager& GetInstance()
		{
			static CollisionManager instance;
			return instance;
		}
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;

		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();

		void CheckLayerCollision(Scene* pScene, const eLayerType eLeftLayer, const eLayerType eRightLayer);
		void CollisionLayerCheck(const eLayerType eLeftLayer, const eLayerType eRightLayer, bool bIsEnable = true);
		void CheckValidColliderCollision(Collider2D* pLeftCollider, Collider2D* pRightCollider);
		bool Intersect(Collider2D* pLeftCollider, Collider2D* pRightCollider);

	private:
		std::bitset<static_cast<UINT>(eLayerType::COUNT)> mLayerCollisionMatrix[static_cast<UINT>(eLayerType::COUNT)];
		std::unordered_map<UINT64, bool> mCollisionMap;

		CollisionManager() = default;
		~CollisionManager() = default;
	};
}

