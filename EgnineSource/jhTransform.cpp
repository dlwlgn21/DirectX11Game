#include "jhTransform.h"
#include "jhRenderer.h"
#include "jhConstantBuffer.h"

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
		WriteContantBufferAtGPUAndSetConstantBufferAtShader();
	}
	void Transform::Render()
	{
	}

	void Transform::WriteContantBufferAtGPUAndSetConstantBufferAtShader()
	{
		Vector4 passVector(mPosition.x, mPosition.y, mPosition.z, 0.0f);
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)];
		pConstantBuffer->WriteConstantBufferAtGPU(&passVector);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
	}
}