#include "jhMaterial.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhConstantBuffer.h"

using namespace jh::graphics;

namespace jh
{
	Material::Material()
		: Resource(eResourceType::METERIAL)
		, mpShader(nullptr)
		, mMaterialConstantBuffer{}
		, mpTexture(nullptr)
	{
		ZeroMemory(&mMaterialConstantBuffer, sizeof(MaterialConstantBuffer));
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{

		return S_OK;
	}

	void Material::SetDataAtConstantBuffer(eGPUPrameterType eGPUParamType, void* pData)
	{
		switch (eGPUParamType)
		{
		case eGPUPrameterType::INT:
			mMaterialConstantBuffer.iData = *static_cast<int*>(pData);
			break;
		case eGPUPrameterType::FLOAT:
			mMaterialConstantBuffer.fData = *static_cast<float*>(pData);

			break;
		case eGPUPrameterType::VECTOR2:
			mMaterialConstantBuffer.Xy = *static_cast<Vector2*>(pData);

			break;
		case eGPUPrameterType::VECTOR3:
			mMaterialConstantBuffer.Xyz = *static_cast<Vector3*>(pData);

			break;
		case eGPUPrameterType::VECTOR4:
			mMaterialConstantBuffer.Xyzw = *static_cast<Vector4*>(pData);

			break;
		case eGPUPrameterType::MATRIX:
			mMaterialConstantBuffer.Matrix = *static_cast<Matrix*>(pData);
			break;
		default:
			assert(false);
			break;
		}
	}
	void Material::BindConstantBufferAndShaderAndSetTextureSRVAtShader()
	{
		assert(mpTexture != nullptr);
		mpTexture->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0);

		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)];
		assert(pConstantBuffer != nullptr);
		pConstantBuffer->WriteConstantBufferAtGPU(&mMaterialConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
		assert(mpShader != nullptr);
		mpShader->SetPrimitiveTopologyAndIASetVertexAndPixelShader();
	}

	void Material::Clear()
	{
		mpTexture->Clear();
	}
}