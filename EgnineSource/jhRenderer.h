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
		Vector3 Position;
		Vector4 Color;
		Vector2 UV;
	};

	extern Vertex											vertices[VERTEX_COUNT];
	extern ConstantBuffer*									pConstantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>		cpSamplerState[];

	__forceinline void ifFailed(HRESULT hr) { if (FAILED(hr)) { assert(false); } }
	void Initialize();
	void Release();

}

