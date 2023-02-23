#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhTexture.h"


using namespace jh::graphics;
namespace jh::renderer
{

	Vertex											vertices[VERTEX_COUNT]{};
	ConstantBuffer*									pConstantBuffers[static_cast<UINT>(eConstantBufferType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState>		cpSamplerStates[static_cast<UINT>(graphics::eSamplerType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	cpRasterizerStates[static_cast<UINT>(graphics::eRasterizerStateType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	cpDepthStencilStates[static_cast<UINT>(graphics::eDepthStencilStateType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState>		cpBlendStates[static_cast<UINT>(graphics::eBlendStateType::COUNT)] = {};
	std::vector<Camera*>							pCameras;


	/*
	Resources::Load<Texture>(L"GennaroTexture", L"Gennaro.bmp");
		Resources::Load<Texture>(L"DefaultTexture", L"DefaultTexture.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
	
	*/


	static const std::wstring RECT_SHADER_KEY = L"RectShader";
	static const std::wstring SPRITE_SHADER_KEY = L"SpriteShader";
	static const std::wstring UI_SHADER_KEY = L"UIShader";
	static const std::wstring GRID_SHADER_KEY = L"GridShader";

	static const std::wstring GENNARO_TEXTURE_KEY = L"GennaroTexture";
	static const std::wstring DEFAULT_TEXTURE_KEY = L"DefaultTexture";
	static const std::wstring HPBAR_TEXTURE_KEY = L"HPBarTexture";

	static const std::wstring DEFAULT_MATERIAL_KEY = L"RectMaterial";
	static const std::wstring SPRITE_MATERIAL_KEY = L"SpriteMaterial";
	static const std::wstring UI_MATERIAL_KEY = L"UIMaterial";
	static const std::wstring GRID_MATERIAL_KEY = L"GridMaterial";

	static const std::wstring RECT_MESH_KEY = L"RectMesh";

	__forceinline void LoadAndSetShader()
	{
		// Default
		Shader* pShader = new Shader();
		pShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhVertexShader.hlsl", "main");
		pShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhPixelShader.hlsl", "main");
		Resources::Insert<Shader>(RECT_SHADER_KEY, pShader);


		// Sprite
		Shader* pSpriteShader = new Shader();
		pSpriteShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"SpriteVertexShader.hlsl", "main");
		pSpriteShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"SpritePixelShader.hlsl", "main");
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

	}

	__forceinline void SetupInputLayout()
	{
		Shader* pRectShader = Resources::Find<Shader>(RECT_SHADER_KEY);
		Shader* pSpriteShader = Resources::Find<Shader>(SPRITE_SHADER_KEY);
		Shader* pUIShader = Resources::Find<Shader>(UI_SHADER_KEY);
		Shader* pGridShader = Resources::Find<Shader>(GRID_SHADER_KEY);
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
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, cpBlendStates[static_cast<UINT>(eBlendStateType::ALPHA_BLEND)].GetAddressOf());

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		GetDevice()->CreateBlendState(&blendDesc, cpBlendStates[static_cast<UINT>(eBlendStateType::ONE_ONE)].GetAddressOf());
	}

	__forceinline void CreateVertexAndIndexBuffer()
	{
		Mesh* pMesh = new Mesh();
		Resources::Insert<Mesh>(RECT_MESH_KEY, pMesh);
		pMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);
		// ÀÎµ¦½º ¹öÆÛ
		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		pMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
	}

	__forceinline void CreateConstantBuffer()
	{
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)] = new ConstantBuffer(eConstantBufferType::TRANSFORM);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)]->CreateBuffer(sizeof(TransformConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)] = new ConstantBuffer(eConstantBufferType::MATERIAL);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)]->CreateBuffer(sizeof(MaterialConstantBuffer));

		pConstantBuffers[static_cast<UINT>(eConstantBufferType::GRID)] = new ConstantBuffer(eConstantBufferType::GRID);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::GRID)]->CreateBuffer(sizeof(GridConstantBuffer));
	}

	__forceinline void CreateMeterial() {

		// Default
		Material* pDefaultMaterial = new Material();
		pDefaultMaterial->SetShader(Resources::Find<Shader>(RECT_SHADER_KEY));
		Texture* pTexture = Resources::Find<Texture>(GENNARO_TEXTURE_KEY);
		assert(pTexture != nullptr); 
		pDefaultMaterial->SetTexture(pTexture);
		Resources::Insert<Material>(DEFAULT_MATERIAL_KEY, pDefaultMaterial);



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
	}

	__forceinline void CreateTexture()
	{
		Resources::Load<Texture>(GENNARO_TEXTURE_KEY, L"Gennaro.bmp");
		Resources::Load<Texture>(DEFAULT_TEXTURE_KEY, L"DefaultTexture.png");
		Resources::Load<Texture>(HPBAR_TEXTURE_KEY, L"HPBar.png");
	}

	void Initialize()
	{
		pCameras.reserve(8);
		//pCameras.resize(pCameras.capacity());

		vertices[0].Position =	Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
		vertices[0].Color =		Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertices[0].UV =		Vector2(0.0f, 0.0f);

		vertices[1].Position =	Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		vertices[1].Color =		Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[1].UV =		Vector2(1.0f, 0.f);

		vertices[2].Position =	Vector4(0.5f, -0.5f, 0.5f, 1.0f);
		vertices[2].Color =		Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertices[2].UV =		Vector2(1.0f, 1.0f);

		vertices[3].Position =	Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
		vertices[3].Color =		Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertices[3].UV =		Vector2(0.0f, 1.0f);

		LoadAndSetShader();
		CreateSamplerState();
		CreateRasterizerDepthStencilBlendState();
		SetupInputLayout();
		CreateVertexAndIndexBuffer();
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
	}

	void Render()
	{
		for (auto* pCam : pCameras)
		{
			if (pCam == nullptr)
				{ continue; }
			pCam->Render();
		}

		pCameras.clear();
	}
}