#pragma once
#include <wrl.h>
#include "jhMath.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT_##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM (0)
#define CBSLOT_MATERIAL (1)
#define CBSLOT_GRID (2)
#define CBSLOT_FADE_OUT (3)
#define CBSLOT_ANIMATOR (4)

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
	enum class eRenderingMode
	{
		OPAQUEE,					// 투명한 영역이 없음
		CUTOUT,						// 투명영역과 불투명 영역 사이에 하드엣지가 있는 투명효과를 만들 수 있음(나뭇잎).
		TRANSPARENTT,
		COUNT
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

	enum class eRasterizerStateType
	{
		SOLID_BACK,
		SOLID_FRONT,
		SOLID_NONE,
		WIRE_FRAME_NONE,
		COUNT
	};
	
	enum class eDepthStencilStateType
	{
		LESS_FIRST,
		GREATER_FISRT,
		NO_WRITE,
		NONE,
		COUNT
	};

	enum class eBlendStateType
	{
		DEFAULT,
		ALPHA_BLEND,
		ONE_ONE,
		COUNT
	};

	enum class eConstantBufferType
	{
		TRANSFORM,
		MATERIAL,
		GRID,
		FADE_OUT,
		ANIMATION,
		COUNT
	};

	enum class eGPUPrameterType
	{
		INT,
		FLOAT,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		MATRIX,
		COUNT
	};

	enum class eAnimatnionType
	{
		NO_ANIMATION,
		SECOND_DIMENTION,
		THIRD_DIMENTION,
		COUNT
	};
	struct DebugMesh
	{
		eColliderType EColliderType;
		math::Vector3 Position;
		math::Vector3 Rotation;
		math::Vector3 Scale;
		float Radius;
		float Duration;
		float Time;
	};

}