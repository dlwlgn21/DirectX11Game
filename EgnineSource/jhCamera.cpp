#include "jhCamera.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhApplication.h"



namespace jh
{

	Matrix Camera::sViewMat = Matrix::Identity;
	Matrix Camera::sProjectionMat = Matrix::Identity;


	Camera::Camera()
		: Component(eComponentType::CAMERA)
		, meProjectionType(eProjectionType::PERSPECTIVE)
		, mAspectRatio(1.0f)
		, mNearPlain(1.0f)
		, mFarPlain(1000.0f)
		, mScale(1.0f)
		, mViewMat(Matrix::Identity)
		, mProjectionMat(Matrix::Identity)
	{
	}

	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
		
	}
	void Camera::Render()
	{
	}


	void Camera::CreateViewMatrix()
	{
		Transform* pTransform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);

		// translation info
		Vector3 pos = pTransform->GetPosition();

		// Create Translation View Matrix
		sViewMat = Matrix::Identity;
		sViewMat *= Matrix::CreateTranslation(-pos);


		// rotation info
		Vector3 upVector = pTransform->GetUp();
		Vector3 rightVector = pTransform->GetRight();
		Vector3 forwardVector = pTransform->GetForward();


		Matrix viewRotationMat;
		viewRotationMat._11 = rightVector.x;	viewRotationMat._12 = upVector.x;	viewRotationMat._13 = forwardVector.x;
		viewRotationMat._21 = rightVector.y;	viewRotationMat._22 = upVector.y;	viewRotationMat._23 = forwardVector.y;
		viewRotationMat._31 = rightVector.z;	viewRotationMat._32 = upVector.z;	viewRotationMat._33 = forwardVector.z;
		
		sViewMat *= viewRotationMat;

	}
	void Camera::CreateProjectionMatrix()
	{
		RECT windowRect;
		ZeroMemory(&windowRect, sizeof(RECT));

		GetClientRect(Application::GetInstance().GetHwnd(), &windowRect);

		float width = static_cast<float>(windowRect.right - windowRect.left);
		float height = static_cast<float>(windowRect.bottom - windowRect.top);

		mAspectRatio = width / height;

		switch (meProjectionType)
		{
		case eProjectionType::PERSPECTIVE:
			sProjectionMat = Matrix::CreatePerspectiveFieldOfViewLH(
				XM_2PI / 6.0f,								// 60µµ
				mAspectRatio,
				mNearPlain,
				mFarPlain
			);
			break;
		case eProjectionType::ORTHOGRAPHIC:
			sProjectionMat = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNearPlain, mFarPlain);
			break;
		default:
			assert(false);
			break;
		}
	}
}