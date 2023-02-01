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
		// ConstantBuffer를 가져와서 해당 ConstantBuffer에
		// SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER, eCBType::TRANSFORM, renderer::cpConstantBuffer.Get());
		// 예시처럼 값을 세팅해주어야 한다.
		
	}
}