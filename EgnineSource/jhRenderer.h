#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDeviceDX11.h"


#include "jhMesh.h"
#include "jhShader.h"
constexpr const UINT VERTEX_COUNT = 4;

using namespace jh::math;

namespace jh::renderer
{
	struct Vertex
	{
		FLOAT X, Y, Z;
		FLOAT Color[4];
	};

	extern Vertex											vertices[VERTEX_COUNT];
	extern Mesh*											pMesh;
	extern Shader*											pShader;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>				cpConstantBuffer;


	__forceinline void ifFailed(HRESULT hr) { if (FAILED(hr)) { assert(false); } }
	void Initialize();
	void Release();

}

