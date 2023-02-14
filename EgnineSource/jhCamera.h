#pragma once
#include "jhComponent.h"

using namespace jh::math;
namespace jh
{
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

	private:
		static Matrix sViewMat;
		static Matrix sProjectionMat;


		Matrix mViewMat;
		Matrix mProjectionMat;

		const eProjectionType meProjectionType;

		float mAspectRatio;
		float mNearPlain;
		float mFarPlain;
		float mScale;


	};
}

