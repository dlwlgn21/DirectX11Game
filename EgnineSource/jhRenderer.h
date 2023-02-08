#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDeviceDX11.h"


#include "jhMesh.h"
#include "jhShader.h"
#include "jhConstantBuffer.h"

constexpr const UINT VERTEX_COUNT = 4;

using namespace jh::math;
using namespace jh::graphics;

namespace jh::renderer
{
	struct Vertex
	{
		Vector4 Position;
		Vector4 Color;
		Vector2 UV;
	};

	CBUFFER(TransformConstantBuffer, CBSLOT_TRANSFORM)
	{
		Vector4 Pos;
	};
	CBUFFER(MaterialConstantBuffer, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 Xy;
		Vector3 Xyz;
		Vector4 Xyzw;
		Matrix Matrix;
	};

	extern Vertex											vertices[VERTEX_COUNT];
	extern ConstantBuffer*									pConstantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>		cpSamplerState[];

	__forceinline void ifFailed(HRESULT hr) { if (FAILED(hr)) { assert(false); } }
	void Initialize();
	void Release();

}

