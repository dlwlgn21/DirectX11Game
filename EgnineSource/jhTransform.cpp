#include "jhTransform.h"
#include "jhRenderer.h"
#include "jhConstantBuffer.h"
#include "jhCamera.h"


namespace jh
{
	Transform::Transform()
		: Component(eComponentType::TRANSFORM)
		, mForwardVector(Vector3::Forward)
		, mRightVector(Vector3::Right)
		, mUpVector(Vector3::Up)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mpParent(nullptr)
	{
		ZeroMemory(&mWorldMat, sizeof(Matrix));
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
		// 렌더링에 사용 될 위치값들을 업데이트
	}
	void Transform::FixedUpdate()
	{
		// 렌더링에 사용 될 위치값들을 업데이트

		// 월드행렬 생성

		Matrix scaleMat = Matrix::CreateScale(mScale);

		Matrix rotationMat;
		rotationMat = Matrix::CreateRotationX(mRotation.x);
		rotationMat *= Matrix::CreateRotationY(mRotation.y);
		rotationMat *= Matrix::CreateRotationZ(mRotation.z);

		Matrix translationMat;
		//translationMat = Matrix::CreateTranslation(mPosition);
		translationMat.Translation(mPosition);

		mWorldMat = scaleMat * rotationMat * translationMat;

		mForwardVector = Vector3::TransformNormal(Vector3::Forward, rotationMat);
		mRightVector = Vector3::TransformNormal(Vector3::Right, rotationMat);
		mUpVector = Vector3::TransformNormal(Vector3::Up, rotationMat);


		// 카메라 컴포넌트에서 세팅해줄 것.
		// 뷰행렬 세팅
		// 프로젝션 행렬 세팅

		// 해당 값들을 상수버퍼에 세팅

		//WriteContantBufferAtGPUAndSetConstantBufferAtShader();

		if (mpParent != nullptr)
		{
			mWorldMat *= mpParent->mWorldMat; // 부모좌표 따라가는 것. 내 월드에 부모월드 곱해주면, 부모좌표를 따라다닌다.
		}
	}
	void Transform::Render()
	{
	}

	void Transform::WriteContantBufferAtGPUAndSetConstantBufferAtShader()
	{
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)];
		assert(pConstantBuffer != nullptr);

		renderer::TransformConstantBuffer transformConstantBuffer;
		ZeroMemory(&transformConstantBuffer, sizeof(renderer::TransformConstantBuffer));
		transformConstantBuffer.WroldMat = mWorldMat;
		transformConstantBuffer.ViewMat = Camera::GetGPUViewMatrix();
		transformConstantBuffer.ProjectionMat = Camera::GetGPUProjectionMatrix();

		pConstantBuffer->WriteConstantBufferAtGPU(&transformConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
	}
}