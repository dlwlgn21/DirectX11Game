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

}