#pragma once
#include "jhComponent.h"

using namespace jh::math;
namespace jh
{
	class RendererComponent;
	class Camera final : public Component
	{
	public:
		enum class eProjectionType
		{
			PERSPECTIVE,
			ORTHOGRAPHIC,
			COUNT
		};

		__forceinline static const Matrix& GetViewMatrix()			{ return sViewMat; }
		__forceinline static const Matrix& GetProjectionMatrix()	{ return sProjectionMat; }

		Camera();
		virtual ~Camera();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();

		void TurnLayerMasks(const eLayerType eLayer, const bool bEnable = true);
		void EnableAllLayerMasks() { mLayerMasks.set(); }
		void DisableAllLayerMasks() { mLayerMasks.reset(); }
		
		void setProjectionType(const eProjectionType eType) { meProjectionType = eType; }

	private:
		void registerCameraAtRenderer();
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectByMaterialRenderingMode(RendererComponent* pRenderer, GameObject* pGameObject);

	private:
		static Matrix sViewMat;
		static Matrix sProjectionMat;

		Matrix mViewMat;
		Matrix mProjectionMat;

		eProjectionType meProjectionType;

		float mAspectRatio;
		float mNearPlain;
		float mFarPlain;
		float mScale;
		
		std::bitset<static_cast<UINT>(eLayerType::COUNT)> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutObjects;
		std::vector<GameObject*> mTransparentObjects;


	};
}

