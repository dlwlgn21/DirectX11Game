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
#define CBSLOT_TRANSLATE_UV (3)
#define CBSLOT_ANIMATOR (4)
#define CBSLOT_NUMBER_OF_LIGHT (5)
#define CBSLOT_PARTICLE_SYSTEM (6)

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
		COMPUTE_SHADER,
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

		D3D11_BUFFER_DESC BufferDesc = {};
		Microsoft::WRL::ComPtr<ID3D11Buffer> CpBuffer;

		GPUBuffer() = default;
		virtual ~GPUBuffer()
		{
			CpBuffer.Reset();
		}
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
		TRANSLATE_UV,
		ANIMATION,
		LIGHT,
		PARTICLE_SYSTEM,
		COUNT
	};

	enum class eGPUPrameterType
	{
		FLOAT,
		COUNT
	};

	enum class eAnimatnionType
	{
		NO_ANIMATION,
		SECOND_DIMENTION,
		THIRD_DIMENTION,
		COUNT
	};
	enum class eShaderResourceViewType
	{
		NONE,
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

	struct LightAttribute
	{
		math::Vector4 DiffuseLight;			// 분산광 물체의 표면에서 분산되어 눈으로 바로 들어오는 빛. 각도에 따라 밝기가 다르다.
		math::Vector4 SpcularLight;			// 반사광 분산광과 달리 한방향으로 완전히 반사되는 빛. 반사되는 부분은 흰색의 광으로 보인다. 즉 하이라이트
		math::Vector4 AmbientLight;			// 주변광 수많은 반사를 거쳐서 광원이 불분명한 빛.	물체를 덮고 있는 빛이며 일정한 밝기의 색으로 표시한다.
		//math::Vector4 EmissiveLight;		// 발광체 물체자체가 빛나고 있는 빛.
		math::Vector4 Position;
		math::Vector4 Direction;
		eLightType ELightType;
		float Radius;						// 빛의 영향을 받는 범위
		float Angle;
		int padding;
		LightAttribute()
			: DiffuseLight(math::Vector4(0.0f, 0.0f, 0.0f, 0.0f))
			, AmbientLight(math::Vector4(0.0f, 0.0f, 0.0f, 0.0f))
			//, EmissiveLight(math::Vector4(0.0f, 0.0f, 0.0f, 0.0f))
			, Position(math::Vector4(0.0f, 0.0f, 0.0f, 0.0f))
			, Direction(math::Vector4(0.0f, 0.0f, 0.0f, 0.0f))
			, ELightType(eLightType::DIRECTIONAL_LIGHT)
			, Radius(0.0f)
			, Angle(0.0f)
			, padding(0)
		{
		}
	};

	struct Particle
	{
		math::Vector4 Position;
		math::Vector4 Direction;
		
		float LifeTime;
		float CurrTime;
		float Speed;
		UINT Active;
	};
}