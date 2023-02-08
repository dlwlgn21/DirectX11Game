#include "jhMaterial.h"
#include "jhShader.h"

using namespace jh::graphics;

namespace jh
{
	Material::Material()
		: Resource(eResourceType::METERIAL)
	{
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
			break;
		case eGPUPrameterType::FLOAT:
			break;
		case eGPUPrameterType::VECTOR2:
			break;
		case eGPUPrameterType::VECTOR3:
			break;
		case eGPUPrameterType::VECTOR4:
			break;
		case eGPUPrameterType::MATRIX:
			break;
		default:
			assert(false);
			break;
		}
	}
	void Material::WriteConstantBufferAtGPU()
	{
	}
}