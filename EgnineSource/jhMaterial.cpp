#include "jhMaterial.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhConstantBuffer.h"


#include "jhPaintShader.h"
#include "jhTime.h"

using namespace jh::graphics;

namespace jh
{
	Material::Material()
		: Resource(eResourceType::METERIAL)
		, mpShader(nullptr)
		, mMaterialConstantBuffer{}
		, mpTexture(nullptr)
		, meRenderingMode(eRenderingMode::OPAQUEE)
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

	void Material::SetDataAtConstantBuffer(const eGPUPrameterType eGPUParamType, void* pData)
	{
		switch (eGPUParamType)
		{
		case eGPUPrameterType::FLOAT:
			mMaterialConstantBuffer.fData = *static_cast<float*>(pData);
			break;
		default:
			assert(false);
			break;
		}
	}
	void Material::BindConstantBufferAndShaderAndSetTextureSRVAtShader()
	{
		//assert(mpTexture != nullptr);
		if (mpTexture != nullptr)
		{
			// ��� Shader�� texture2D defaultTexture : register(t0)�� �����. t0 �׸��ϱ� 0�� ���� �̶�� ��.
			mpTexture->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0);
			
		}

		// AddedPART
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)];
		assert(pConstantBuffer != nullptr);
		//SetDataAtConstantBuffer(eGPUPrameterType::FLOAT, &mAccum);

		pConstantBuffer->WriteConstantBufferAtGPU(&mMaterialConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::GEOMETRY_SHADER);
		assert(mpShader != nullptr);
		mpShader->SetPrimitiveTopologyAndIASetVertexAndPixelShader();
	}

	void Material::Clear()
	{
		mpTexture->Clear();
	}


}