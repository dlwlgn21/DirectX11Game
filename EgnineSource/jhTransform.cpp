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
		// �������� ��� �� ��ġ������ ������Ʈ
	}
	void Transform::FixedUpdate()
	{
		// �������� ��� �� ��ġ������ ������Ʈ

		// ������� ����

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


		// ī�޶� ������Ʈ���� �������� ��.
		// ����� ����
		// �������� ��� ����

		// �ش� ������ ������ۿ� ����

		//WriteContantBufferAtGPUAndSetConstantBufferAtShader();

		if (mpParent != nullptr)
		{
			mWorldMat *= mpParent->mWorldMat; // �θ���ǥ ���󰡴� ��. �� ���忡 �θ���� �����ָ�, �θ���ǥ�� ����ٴѴ�.
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