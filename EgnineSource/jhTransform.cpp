#include "jhTransform.h"
#include "jhRenderer.h"


namespace jh
{
	Transform::Transform()
		: Component(eComponentType::TRANSFORM)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::FixedUpdate()
	{
	}
	void Transform::Render()
	{
	}

	void Transform::SetConstantBufferAtGPU()
	{
		// ConstantBuffer�� �����ͼ� �ش� ConstantBuffer��
		// SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER, eCBType::TRANSFORM, renderer::cpConstantBuffer.Get());
		// ����ó�� ���� �������־�� �Ѵ�.
		
	}
}