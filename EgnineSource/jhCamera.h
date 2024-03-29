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

		__forceinline static const Matrix& GetGPUViewMatrix()			{ return sViewMat; }
		__forceinline static const Matrix& GetGPUProjectionMatrix()	{ return sProjectionMat; }
		__forceinline static void SetGPUViewMatrix(const Matrix viewMat) { sViewMat = viewMat; }
		__forceinline static void SetGPUProjectionMatrix(const Matrix progectionMat) { sProjectionMat = progectionMat; }

		Camera();
		virtual ~Camera() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();

		void TurnLayerMasks(const eLayerType eLayer, const bool bEnable = true);
		void EnableAllLayerMasks() { mLayerMasks.set(); }
		void DisableAllLayerMasks() { mLayerMasks.reset(); }
		
		void SetProjectionType(const eProjectionType eType) { meProjectionType = eType; }

		__forceinline float GetScale() const { return mScale; }
		void registerCameraAtRenderer();

		__forceinline const Matrix& GetViewMatrix() { return mViewMat; }
		__forceinline const Matrix& GetProjectionMatrix() { return mProjectionMat; }

	private:
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

