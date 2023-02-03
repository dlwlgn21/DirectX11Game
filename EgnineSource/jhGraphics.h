#pragma once
#include <wrl.h>
#include "jhMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

namespace jh::graphics
{
	enum class eValidationMode
	{
		DISABLED,
		ENABLED,
		GPU,
	};

	enum class eShaderStage
	{
		VERTEX_SHADER,
		HULL_SHADER,
		DOMAIN_SHADER,
		GEOMETRY_SHADER,
		PIXEL_SHADER,
		CS,
		COUNT,
	};

	struct GPUBuffer
	{
		enum class eBufferType
		{
			BUFFER,
			TEXTURE,
			UNKNOWN_TYPE,
		} Type = eBufferType::UNKNOWN_TYPE;

		D3D11_BUFFER_DESC ConstantBufferDesc = {};
		Microsoft::WRL::ComPtr<ID3D11Buffer> CpBuffer;

		GPUBuffer() = default;
		virtual ~GPUBuffer() = default;
	};

	enum class eSamplerType
	{
		POINT,
		LINEAR,
		ANISOTROPIC,
		COUNT
	};
}