#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhTexture.h"
#include "jhSceneManager.h"
#include "jhShader.h"
#include "jhPaintShader.h"

using namespace jh::graphics;
namespace jh::renderer
{
	Vertex											vertices[VERTEX_COUNT]{};
	ConstantBuffer*									pConstantBuffers[static_cast<UINT>(eConstantBufferType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		cpSamplerStates[static_cast<UINT>(graphics::eSamplerType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	cpRasterizerStates[static_cast<UINT>(graphics::eRasterizerStateType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	cpDepthStencilStates[static_cast<UINT>(graphics::eDepthStencilStateType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState>		cpBlendStates[static_cast<UINT>(graphics::eBlendStateType::COUNT)] = {};
	std::vector<Camera*>							pCameras[static_cast<UINT>(eSceneType::COUNT)];
	std::vector<DebugMesh>							debugMeshs;
	std::vector<LightAttribute>						lights;

	Camera*											pMainCamera = nullptr;
	StructuredBuffer*								pLightStructuredBuffer;

	static const std::wstring CHARACTER_SHADER_KEY = L"CharacterShader";
	static const std::wstring SPRITE_SHADER_KEY = L"SpriteShader";
	static const std::wstring UI_SHADER_KEY = L"UIShader";
	static const std::wstring GRID_SHADER_KEY = L"GridShader";
	static const std::wstring FADE_OUT_SHADER_KEY = L"FadeOutShader";
	static const std::wstring DEBUG_SHADER_KEY = L"DebugShader";
	static const std::wstring BACK_GROUND_SHADER_KEY = L"BackGroundShader";
	static const std::wstring PAINT_SHADER_KEY = L"PaintShader";
	static const std::wstring PARTICLE_SHADER_KEY = L"ParticleShader";


	static const std::wstring PLAYER_TEXTURE_KEY = L"PlayerTexture";
	static const std::wstring DEFAULT_TEXTURE_KEY = L"DefaultTexture";
	static const std::wstring HPBAR_TEXTURE_KEY = L"HPBarTexture";
	static const std::wstring FADE_OUT_TEXTURE_KEY = L"FadeOutTexture";
	static const std::wstring MONSTER_TEXTURE_KEY = L"MonsterTexture";
	static const std::wstring TITLE_BACKGROUND_TEXTURE_KEY = L"BackGroundTexture";
	static const std::wstring ZELDA_TEXTURE_KEY = L"ZeldaTexture";
	static const std::wstring ZOMBIE_TEXTURE_KEY = L"WildZombieTexture";
	static const std::wstring BATTLE_SCENE_TEXTURE_KEY = L"BattleSceneTexture";
	static const std::wstring PAINT_TEXTURE_KEY = L"PaintTexture";
	static const std::wstring SMILE_TEXTURE_KEY = L"SmileTexture";

	static const std::wstring PLAYER_MATERIAL_KEY = L"PlayerMaterial";
	static const std::wstring SPRITE_MATERIAL_KEY = L"SpriteMaterial";
	static const std::wstring UI_MATERIAL_KEY = L"UIMaterial";
	static const std::wstring GRID_MATERIAL_KEY = L"GridMaterial";
	static const std::wstring FADE_OUT_MATERIAL_KEY = L"FadeOutMaterial";
	static const std::wstring DEBUG_MATERIAL_KEY = L"DebugMaterial";
	static const std::wstring MONSTER_MATERIAL_KEY = L"MonsterMaterial";
	static const std::wstring TITLE_BACKGROUND_MATERIAL_KEY = L"TitleBackground";
	static const std::wstring PARTICLE_MATERIAL_KEY = L"ParticleMaterial";
	static const std::wstring PAINT_MATERIAL_KEY = L"PaintMaterial";
	
	static const std::wstring RECT_MESH_KEY = L"RectMesh";
	static const std::wstring RECT_DEBUG_MESH_KEY = L"RectDebugMesh";
	static const std::wstring CIRCLE_DEBUG_MESH_KEY = L"CircleDebugMesh";
	static const std::wstring BATTLE_SCENE_MESH_KEY = L"BattleSceneMesh";
	static const std::wstring POINT_MESH_KEY = L"PointMesh";

	__forceinline void CreateMeshAndVertexAndIndexBuffer()
	{
		// Point Mesh For ParticleSystem
		Vertex pointVertex = {};
		Mesh* pPointMesh = new Mesh();
		Resources::Insert<Mesh>(POINT_MESH_KEY, pPointMesh);
		pPointMesh->CreateVertexBuffer(&pointVertex, 1);
		UINT pointIdx = 0;
		pPointMesh->CreateIndexBuffer(&pointIdx, 1);

		const int SLICE_COUNT = 80;
		float radius = 0.5f;
		float theta = XM_2PI / SLICE_COUNT;

		vertices[0].Position = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertices[0].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices[0].UV = Vector2(0.0f, 0.0f);

		vertices[1].Position = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertices[1].Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[1].UV = Vector2(1.0f, 0.f);

		vertices[2].Position = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertices[2].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertices[2].UV = Vector2(1.0f, 1.0f);

		vertices[3].Position = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertices[3].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertices[3].UV = Vector2(0.0f, 1.0f);

		Mesh* pMesh = new Mesh();
		Resources::Insert<Mesh>(RECT_MESH_KEY, pMesh);
		pMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);


		// For BackgroundMesh Texture
		vertices[0].UV = Vector2(0.15f, 0.15f);
		vertices[1].UV = Vector2(0.85f, 0.15f);
		vertices[2].UV = Vector2(0.85f, 0.85f);
		vertices[3].UV = Vector2(0.15f, 0.85f);

		Mesh* pBackgroundMesh = new Mesh();
		Resources::Insert<Mesh>(BATTLE_SCENE_MESH_KEY, pBackgroundMesh);
		pBackgroundMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);

		// 인덱스 버퍼
		std::vector<UINT> indexes;
		indexes.reserve(SLICE_COUNT);
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		pMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		pBackgroundMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));

		vertices[0].Position = Vector4(-0.5f, 0.5f, -0.01f, 1.0f);
		vertices[0].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices[0].UV = Vector2(0.0f, 0.0f);

		vertices[1].Position = Vector4(0.5f, 0.5f, -0.01f, 1.0f);
		vertices[1].Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[1].UV = Vector2(1.0f, 0.0f);

		vertices[2].Position = Vector4(0.5f, -0.5f, -0.01f, 1.0f);
		vertices[2].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertices[2].UV = Vector2(1.0f, 1.0f);

		vertices[3].Position = Vector4(-0.5f, -0.5f, -0.01f, 1.0f);
		vertices[3].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertices[3].UV = Vector2(0.0f, 1.0f);


		// Create RectDebugMesh
		Mesh* pDebugMesh = new Mesh();
		pDebugMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);
		pDebugMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		Resources::Insert<Mesh>(RECT_DEBUG_MESH_KEY, pDebugMesh);

		// Create CircleDebugMesh
		std::vector<Vertex> circleVertexs;

		Vertex center = {};
		center.Position = Vector4(0.0f, 0.0f, -0.1f, 1.0f);
		center.Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		circleVertexs.reserve(SLICE_COUNT + 2);
		circleVertexs.push_back(center);

		for (int i = 0; i < SLICE_COUNT; ++i)
		{
			Vertex vertex = {};
			vertex.Position = Vector4(
				radius * cosf(theta * i),
				radius * sinf(theta * i),
				-0.1f,
				1.0f
			);
			vertex.Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			circleVertexs.push_back(vertex);
		}

		indexes.clear();
		for (UINT i = 0; i < SLICE_COUNT - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		Mesh* pCircleMesh = new Mesh();
		Resources::Insert<Mesh>(CIRCLE_DEBUG_MESH_KEY, pCircleMesh);
		pCircleMesh->CreateVertexBuffer(circleVertexs.data(), static_cast<UINT>(circleVertexs.size()));
		pCircleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));

	}

	__forceinline void LoadAndSetShader()
	{
		// Default
		Shader* pShader = new Shader();
		pShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhCharacterVertexShader.hlsl", "main");
		pShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhCharacterPixelShader.hlsl", "main");
		Resources::Insert<Shader>(CHARACTER_SHADER_KEY, pShader);


		// Sprite
		Shader* pSpriteShader = new Shader();
		pSpriteShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhSpriteVertexShader.hlsl", "main");
		pSpriteShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhSpritePixelShader.hlsl", "main");
		pSpriteShader->SetRasterizerState(eRasterizerStateType::SOLID_NONE);
		pSpriteShader->SetDepthStencilState(eDepthStencilStateType::LESS_FIRST);
		pSpriteShader->SetBlendState(eBlendStateType::ONE_ONE);
		
		Resources::Insert<Shader>(SPRITE_SHADER_KEY, pSpriteShader);

		// UI
		Shader* pUIShader = new Shader();
		pUIShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhUIVertexShader.hlsl", "main");
		pUIShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhUIPixelShader.hlsl", "main");
		Resources::Insert<Shader>(UI_SHADER_KEY, pUIShader);


		// GridShader
		Shader* pGridShader = new Shader();
		pGridShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhGridVertexShader.hlsl", "main");
		pGridShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhGridPixelShader.hlsl", "main");

		pGridShader->SetRasterizerState(eRasterizerStateType::SOLID_NONE);
		pGridShader->SetDepthStencilState(eDepthStencilStateType::NO_WRITE);
		pGridShader->SetBlendState(eBlendStateType::ALPHA_BLEND);

		Resources::Insert<Shader>(GRID_SHADER_KEY, pGridShader); 


		// FadeOutShader
		Shader* pFadeOutShader = new Shader();
		pFadeOutShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhFadeOutVertexShader.hlsl", "main");
		pFadeOutShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhFadeOutPixelShader.hlsl", "main");
		Resources::Insert<Shader>(FADE_OUT_SHADER_KEY, pFadeOutShader);

		// DebugShader
		Shader* pDebugShader = new Shader();
		pDebugShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhDebugVertexShader.hlsl", "main");
		pDebugShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhDebugPixelShader.hlsl", "main");
		pDebugShader->SetRasterizerState(eRasterizerStateType::SOLID_NONE);
		pDebugShader->SetDepthStencilState(eDepthStencilStateType::NO_WRITE);
		pDebugShader->SetBlendState(eBlendStateType::ALPHA_BLEND);
		pDebugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Resources::Insert<Shader>(DEBUG_SHADER_KEY, pDebugShader);

		// BackgroundShader
		Shader* pBackgroundShader = new Shader();
		pBackgroundShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhBackGroundVertexShader.hlsl", "main");
		pBackgroundShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhBackGroundPixelShader.hlsl", "main");
		Resources::Insert<Shader>(BACK_GROUND_SHADER_KEY, pBackgroundShader);

		// PaintShader
		{
			//PaintShader* pPaintShader = new PaintShader();
			//pPaintShader->Create(L"PaintComputeShader.hlsl", "main");
			//Resources::Insert<ComputeShader>(PAINT_SHADER_KEY, pPaintShader);
		}


		// ParticleShader
		Shader* pParticleShader = new Shader();
		pParticleShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhParticleVertexShader.hlsl", "main");
		pParticleShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhParticlePixelShader.hlsl", "main");
		pParticleShader->Create(graphics::eShaderStage::GEOMETRY_SHADER, L"jhParticleGeometryShader.hlsl", "main");
		pParticleShader->SetRasterizerState(eRasterizerStateType::SOLID_NONE);
		pParticleShader->SetDepthStencilState(eDepthStencilStateType::NO_WRITE);
		pParticleShader->SetBlendState(eBlendStateType::ALPHA_BLEND);
		pParticleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(PARTICLE_SHADER_KEY, pParticleShader);

	}

	__forceinline void SetupInputLayout()
	{
		Shader* pRectShader =		Resources::Find<Shader>(CHARACTER_SHADER_KEY);
		Shader* pSpriteShader =		Resources::Find<Shader>(SPRITE_SHADER_KEY);
		Shader* pUIShader =			Resources::Find<Shader>(UI_SHADER_KEY);
		Shader* pGridShader =		Resources::Find<Shader>(GRID_SHADER_KEY);
		Shader* pFadeOutShader =	Resources::Find<Shader>(FADE_OUT_SHADER_KEY);
		Shader* pDebugShader =		Resources::Find<Shader>(DEBUG_SHADER_KEY);
		Shader* pBackgroundShader =	Resources::Find<Shader>(BACK_GROUND_SHADER_KEY);
		Shader* pParticleShader =	Resources::Find<Shader>(PARTICLE_SHADER_KEY);

		const UINT ELEMENT_DESC_COUNT = 3;
		D3D11_INPUT_ELEMENT_DESC inputDesc[ELEMENT_DESC_COUNT] = {};


		inputDesc[0].AlignedByteOffset =			0;
		inputDesc[0].Format =						DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputDesc[0].InputSlot =					0;
		inputDesc[0].InputSlotClass =				D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[0].SemanticName =					"POSITION";
		inputDesc[0].SemanticIndex =				0;

		inputDesc[1].AlignedByteOffset =			16;
		inputDesc[1].Format =						DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputDesc[1].InputSlot =					0;
		inputDesc[1].InputSlotClass =				D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[1].SemanticName =					"COLOR";
		inputDesc[1].SemanticIndex =				0;

		inputDesc[2].AlignedByteOffset =			32;
		inputDesc[2].Format =						DXGI_FORMAT_R32G32_FLOAT;
		inputDesc[2].InputSlot =					0;
		inputDesc[2].InputSlotClass =				D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[2].SemanticName =					"TEXCOORD";
		inputDesc[2].SemanticIndex =				0;

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pRectShader->GetVertexShaderBlob(),
			pRectShader->GetVertexShaderBlobSize(),
			pRectShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pSpriteShader->GetVertexShaderBlob(),
			pSpriteShader->GetVertexShaderBlobSize(),
			pSpriteShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pUIShader->GetVertexShaderBlob(),
			pUIShader->GetVertexShaderBlobSize(),
			pUIShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pGridShader->GetVertexShaderBlob(),
			pGridShader->GetVertexShaderBlobSize(),
			pGridShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pFadeOutShader->GetVertexShaderBlob(),
			pFadeOutShader->GetVertexShaderBlobSize(),
			pFadeOutShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pDebugShader->GetVertexShaderBlob(),
			pDebugShader->GetVertexShaderBlobSize(),
			pDebugShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pBackgroundShader->GetVertexShaderBlob(),
			pBackgroundShader->GetVertexShaderBlobSize(),
			pBackgroundShader->GetInputLayoutAddressOf()
		);

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			ELEMENT_DESC_COUNT,
			pParticleShader->GetVertexShaderBlob(),
			pParticleShader->GetVertexShaderBlobSize(),
			pParticleShader->GetInputLayoutAddressOf()
		);

	}

	__forceinline void CreateSamplerState()
	{
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		graphics::GetDevice()->CreateSamplerState(
			&samplerDesc, 
			cpSamplerStates[static_cast<UINT>(eSamplerType::POINT)].ReleaseAndGetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		graphics::GetDevice()->CreateSamplerState(
			&samplerDesc,
			cpSamplerStates[static_cast<UINT>(eSamplerType::LINEAR)].ReleaseAndGetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		graphics::GetDevice()->CreateSamplerState(
			&samplerDesc,
			cpSamplerStates[static_cast<UINT>(eSamplerType::ANISOTROPIC)].ReleaseAndGetAddressOf()
		);
		
		graphics::GetDevice()->SetSamplerAtALLShaders(
			static_cast<UINT>(eSamplerType::POINT),
			1,
			cpSamplerStates[static_cast<UINT>(eSamplerType::POINT)].GetAddressOf()
		);
		graphics::GetDevice()->SetSamplerAtALLShaders(
			static_cast<UINT>(eSamplerType::LINEAR),
			1,
			cpSamplerStates[static_cast<UINT>(eSamplerType::LINEAR)].GetAddressOf()
		);
		graphics::GetDevice()->SetSamplerAtALLShaders(
			static_cast<UINT>(eSamplerType::ANISOTROPIC),
			1,
			cpSamplerStates[static_cast<UINT>(eSamplerType::ANISOTROPIC)].GetAddressOf()
		);
	}
	__forceinline void CreateRasterizerDepthStencilBlendState() 
	{
		// Rasterizer State
		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&rsDesc, cpRasterizerStates[static_cast<UINT>(eRasterizerStateType::SOLID_BACK)].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rsDesc, cpRasterizerStates[static_cast<UINT>(eRasterizerStateType::SOLID_FRONT)].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, cpRasterizerStates[static_cast<UINT>(eRasterizerStateType::SOLID_NONE)].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, cpRasterizerStates[static_cast<UINT>(eRasterizerStateType::WIRE_FRAME_NONE)].GetAddressOf());

		// DepthStencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, cpDepthStencilStates[static_cast<UINT>(eDepthStencilStateType::LESS_FIRST)].GetAddressOf());

		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		GetDevice()->CreateDepthStencilState(&dsDesc, cpDepthStencilStates[static_cast<UINT>(eDepthStencilStateType::GREATER_FISRT)].GetAddressOf());

		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		GetDevice()->CreateDepthStencilState(&dsDesc, cpDepthStencilStates[static_cast<UINT>(eDepthStencilStateType::NO_WRITE)].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, cpDepthStencilStates[static_cast<UINT>(eDepthStencilStateType::NONE)].GetAddressOf());

		// BlendState
		cpBlendStates[static_cast<UINT>(eBlendStateType::DEFAULT)] = nullptr;
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, cpBlendStates[static_cast<UINT>(eBlendStateType::ALPHA_BLEND)].GetAddressOf());

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;				// SRC -> PixelShader의 출력 RGB값
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;		// Dest-> RenderTarget에 있는 RGB 값
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;				// 위 두 값을 연산하는 방법

		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			// PixelShader의 출력 Alpha값
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;			// RenderTarget에 있는 Alpha 값
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		GetDevice()->CreateBlendState(&blendDesc, cpBlendStates[static_cast<UINT>(eBlendStateType::ONE_ONE)].GetAddressOf());
	}

	__forceinline void CreateConstantBuffer()
	{
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)] = new ConstantBuffer(eConstantBufferType::TRANSFORM);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)]->CreateBuffer(sizeof(TransformConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)] = new ConstantBuffer(eConstantBufferType::MATERIAL);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)]->CreateBuffer(sizeof(MaterialConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::GRID)] = new ConstantBuffer(eConstantBufferType::GRID);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::GRID)]->CreateBuffer(sizeof(GridConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSLATE_UV)] = new ConstantBuffer(eConstantBufferType::TRANSLATE_UV);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSLATE_UV)]->CreateBuffer(sizeof(TranslateUVConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::ANIMATION)] = new ConstantBuffer(eConstantBufferType::ANIMATION);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::ANIMATION)]->CreateBuffer(sizeof(AnimationConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::LIGHT)] = new ConstantBuffer(eConstantBufferType::LIGHT);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::LIGHT)]->CreateBuffer(sizeof(LightConstantBuffer));
	
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::PARTICLE_SYSTEM)] = new ConstantBuffer(eConstantBufferType::PARTICLE_SYSTEM);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::PARTICLE_SYSTEM)]->CreateBuffer(sizeof(ParticleConstantBuffer));

		// StructuredBuffer
		pLightStructuredBuffer = new StructuredBuffer();
		pLightStructuredBuffer->Create(sizeof(LightAttribute), 128, eShaderResourceViewType::NONE, nullptr);
	}

	__forceinline void CreateMeterial() {

		// Player
		Material* pPlayerMaterial = new Material();
		pPlayerMaterial->SetShader(Resources::Find<Shader>(SPRITE_SHADER_KEY));
		Texture* pTexture = Resources::Find<Texture>(PLAYER_TEXTURE_KEY);
		assert(pTexture != nullptr); 
		pPlayerMaterial->SetTexture(pTexture);
		Resources::Insert<Material>(PLAYER_MATERIAL_KEY, pPlayerMaterial);

		// Monster
		Material* pMonsterMaterial = new Material();
		pMonsterMaterial->SetShader(Resources::Find<Shader>(SPRITE_SHADER_KEY));
		Texture* pMonsterTexture = Resources::Find<Texture>(ZOMBIE_TEXTURE_KEY);
		assert(pMonsterTexture != nullptr);
		pMonsterMaterial->SetTexture(pMonsterTexture);
		Resources::Insert<Material>(MONSTER_MATERIAL_KEY, pMonsterMaterial);


		
		Material* pSpriteMaterial = new Material();
		Texture* pSpriteTexture = Resources::Find<Texture>(DEFAULT_TEXTURE_KEY);
		pSpriteMaterial->SetShader(Resources::Find<Shader>(SPRITE_SHADER_KEY));
		pSpriteMaterial->SetTexture(pSpriteTexture);
		Resources::Insert<Material>(SPRITE_MATERIAL_KEY, pSpriteMaterial);

		// UI
		Shader* pUIShader = Resources::Find<Shader>(UI_SHADER_KEY);
		Material* pUIMaterial = new Material();
		pUIMaterial->SetRenderingMode(eRenderingMode::TRANSPARENTT);
		pUIMaterial->SetShader(Resources::Find<Shader>(UI_SHADER_KEY));
		pUIMaterial->SetTexture(Resources::Find<Texture>(HPBAR_TEXTURE_KEY));
		Resources::Insert<Material>(UI_MATERIAL_KEY, pUIMaterial);


		// Grid
		Shader* pGridShader = Resources::Find<Shader>(GRID_SHADER_KEY);
		Material* pGridMaterial = new Material();
		pGridMaterial->SetShader(pGridShader);
		Resources::Insert<Material>(GRID_MATERIAL_KEY, pGridMaterial);

		// FadeOut
		Material* pFadeOutMaterial = new Material();
		pFadeOutMaterial->SetShader(Resources::Find<Shader>(FADE_OUT_SHADER_KEY));
		pFadeOutMaterial->SetTexture(Resources::Find<Texture>(FADE_OUT_TEXTURE_KEY));
		Resources::Insert<Material>(FADE_OUT_MATERIAL_KEY, pFadeOutMaterial);

		// Debug
		Material* pDebugMaterial = new Material();
		pDebugMaterial->SetRenderingMode(eRenderingMode::TRANSPARENTT);
		pDebugMaterial->SetShader(Resources::Find<Shader>(DEBUG_SHADER_KEY));
		Resources::Insert<Material>(DEBUG_MATERIAL_KEY, pDebugMaterial);

		// Background
		Material* pBackgroundMaterial = new Material();
		pBackgroundMaterial->SetShader(Resources::Find<Shader>(BACK_GROUND_SHADER_KEY));
		pBackgroundMaterial->SetTexture(Resources::Find<Texture>(BATTLE_SCENE_TEXTURE_KEY));
		Resources::Insert<Material>(TITLE_BACKGROUND_MATERIAL_KEY, pBackgroundMaterial);

		// Patricle
		Material* pPatricleMaterial = new Material();
		pPatricleMaterial->SetShader(Resources::Find<Shader>(PARTICLE_SHADER_KEY));
		pPatricleMaterial->SetTexture(Resources::Find<Texture>(SMILE_TEXTURE_KEY));
		Resources::Insert<Material>(PARTICLE_MATERIAL_KEY, pPatricleMaterial);


		// ComputeShader
		{
			//Material* pPaintMeterial = new Material();
			//pPaintMeterial->SetShader(Resources::Find<Shader>(SPRITE_SHADER_KEY));
			//pPaintMeterial->SetTexture(Resources::Find<Texture>(PAINT_TEXTURE_KEY));
			//Resources::Insert<Material>(PAINT_MATERIAL_KEY, pPaintMeterial);
		}
		//pPaintMeterial->SetComputeShader(Resources::Find<PaintShader>(PAINT_SHADER_KEY));
	}

	__forceinline void CreateTexture()
	{
		Resources::Load<Texture>(PLAYER_TEXTURE_KEY,			L"CharacterAtlas.png");
		Resources::Load<Texture>(DEFAULT_TEXTURE_KEY,			L"DefaultTexture.png");
		Resources::Load<Texture>(HPBAR_TEXTURE_KEY,				L"HPBar.png");
		Resources::Load<Texture>(FADE_OUT_TEXTURE_KEY,			L"Smile.png");
		Resources::Load<Texture>(MONSTER_TEXTURE_KEY,			L"MonsterIdleImage.png");
		Resources::Load<Texture>(TITLE_BACKGROUND_TEXTURE_KEY,	L"TitleImage.png");
		Resources::Load<Texture>(ZELDA_TEXTURE_KEY,				L"ZeldaSprite.png");
		Resources::Load<Texture>(ZOMBIE_TEXTURE_KEY, 			L"WildZombie.png");
		Resources::Load<Texture>(BATTLE_SCENE_TEXTURE_KEY,		L"Merge.png");
		Resources::Load<Texture>(SMILE_TEXTURE_KEY,				L"CartoonSmoke.png");

		// CreateTexure
		Texture* pUAVTexture = new Texture();
		pUAVTexture->Create(
			1024, 
			1024, 
			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 
			D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS	// 읽기 쓰기 같이 하기 위해서 이렇게 바인드플래그 설정함
		);
		Resources::Insert<Texture>(PAINT_TEXTURE_KEY, pUAVTexture);
	}

	void Initialize()
	{
		lights.reserve(10000);
		for (int i = 0; i < static_cast<UINT>(eSceneType::COUNT); ++i)
		{
			pCameras[i].reserve(8);
		}

		CreateMeshAndVertexAndIndexBuffer();
		LoadAndSetShader();
		CreateSamplerState();
		CreateRasterizerDepthStencilBlendState();
		SetupInputLayout();
		CreateConstantBuffer();
		CreateTexture();
		CreateMeterial();
	}
	void Release()
	{

		for (int i = 0; i < static_cast<UINT>(eConstantBufferType::COUNT); ++i) 
		{
			if (pConstantBuffers[i] == nullptr)
			{
				continue;
			}
			delete pConstantBuffers[i];
			pConstantBuffers[i] = nullptr;
		}
		for (int i = 0; i < static_cast<UINT>(eSamplerType::COUNT); ++i) 
		{
			cpSamplerStates[i].Reset();
		}
		//if (pLightStructuredBuffer != nullptr)
		//{
		//	delete pLightStructuredBuffer;
		//}
	}

	void Render()
	{
		// 라이팅 먼저 적용해준다는 뜻
		BindLightBufferAtGPU();
		eSceneType eCurrSceneType = SceneManager::GetInatance().GetCurrentScene()->GetSceneType();
		for (auto* pCam : pCameras[static_cast<UINT>(eCurrSceneType)])
		{
			if (pCam == nullptr)
				{ continue; }
			pCam->Render();
		}

		pCameras[static_cast<UINT>(eCurrSceneType)].clear();
		lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}
	void BindLightBufferAtGPU()
	{
		pLightStructuredBuffer->BindBufferAtGPU(lights.data(), static_cast<UINT>(lights.size()));
		pLightStructuredBuffer->SetShaderResourceView(eShaderStage::VERTEX_SHADER, StructuredBuffer::TEXTURE_REGISTER_NUMBER);
		pLightStructuredBuffer->SetShaderResourceView(eShaderStage::PIXEL_SHADER, StructuredBuffer::TEXTURE_REGISTER_NUMBER);

		LightConstantBuffer lightConstantBuffer = {};
		lightConstantBuffer.NumberOfLights = static_cast<UINT>(lights.size());
		
		ConstantBuffer* pConstantBuffer = pConstantBuffers[static_cast<UINT>(eConstantBufferType::LIGHT)];
		assert(pConstantBuffer != nullptr);
		pConstantBuffer->WriteConstantBufferAtGPU(&lightConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
}