#pragma once
#include "CommonInclude.h"
#include "jhMath.h"
#include "jhGraphicDeviceDX11.h"


#include "jhMesh.h"
#include "jhShader.h"
#include "jhConstantBuffer.h"
#include "jhCamera.h"

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
		Matrix WroldMat;
		Matrix ViewMat;
		Matrix ProjectionMat;
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
	CBUFFER(GridConstantBuffer, CBSLOT_GRID)
	{
		Vector4 fCameraPosition;
		Vector2 fResolution;
		Vector2 fCameraScale;
	};
	CBUFFER(FadeOutConstantBuffer, CBSLOT_FADE_OUT)
	{
		Vector4 fDeltaTime;
	};

	CBUFFER(AnimationConstantBuffer, CBSLOT_ANIMATOR)
	{
		Vector2 LeftTop;
		Vector2 Size;
		Vector2 Offset;
		Vector2 AtlasImageSize;

		UINT	AnimationType;				// 애니메이션 안 쓸수도 있어서. 배경만 나와야 할 수도 있어서.
	};


	extern Vertex											vertices[VERTEX_COUNT];
	extern ConstantBuffer*									pConstantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>		cpSamplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState>	cpRasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	cpDepthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState>			cpBlendStates[];
	extern std::vector<Camera*>								pCameras[];
	extern std::vector<DebugMesh>							debugMeshs;
	extern Camera*											pMainCamera;

	extern const std::wstring CHARACTER_SHADER_KEY;
	extern const std::wstring SPRITE_SHADER_KEY;
	extern const std::wstring UI_SHADER_KEY;
	extern const std::wstring GRID_SHADER_KEY;
	extern const std::wstring FADE_OUT_SHADER_KEY;
	extern const std::wstring DEBUG_SHADER_KEY;
	extern const std::wstring BACK_GROUND_SHADER_KEY;

	extern const std::wstring PLAYER_TEXTURE_KEY;
	extern const std::wstring DEFAULT_TEXTURE_KEY;
	extern const std::wstring HPBAR_TEXTURE_KEY;
	extern const std::wstring FADE_OUT_TEXTURE_KEY;
	extern const std::wstring MONSTER_TEXTURE_KEY;
	extern const std::wstring TITLE_BACKGROUND_TEXTURE_KEY;

	extern const std::wstring PLAYER_MATERIAL_KEY;
	extern const std::wstring SPRITE_MATERIAL_KEY;
	extern const std::wstring UI_MATERIAL_KEY;
	extern const std::wstring GRID_MATERIAL_KEY;
	extern const std::wstring FADE_OUT_MATERIAL_KEY;
	extern const std::wstring DEBUG_MATERIAL_KEY;
	extern const std::wstring MONSTER_MATERIAL_KEY;
	extern const std::wstring TITLE_BACKGROUND_MATERIAL_KEY;

	extern const std::wstring RECT_MESH_KEY;
	extern const std::wstring RECT_DEBUG_MESH_KEY;
	extern const std::wstring CIRCLE_DEBUG_MESH_KEY;

	__forceinline void ifFailed(HRESULT hr) { if (FAILED(hr)) { assert(false); } }
	void Initialize();
	void Release();
	void Render();

}

