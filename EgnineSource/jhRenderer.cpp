#include "jhRenderer.h"
#include "jhResources.h"
#include "jhMaterial.h"
#include "jhTexture.h"


using namespace jh::graphics;
namespace jh::renderer
{

	Vertex vertices[VERTEX_COUNT]{};
	ConstantBuffer* pConstantBuffers[static_cast<UINT>(eConstantBufferType::COUNT)] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> cpSamplerStates[static_cast<UINT>(graphics::eSamplerType::COUNT)] = {};

	static const std::wstring RECT_SHADER_KEY = L"RectShader";
	static const std::wstring SPRITE_SHADER_KEY = L"SpriteShader";

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

	}

	__forceinline void SetupInputLayout()
	{
		Shader* pRectShader = Resources::Find<Shader>(RECT_SHADER_KEY);
		Shader* pSpriteShader = Resources::Find<Shader>(SPRITE_SHADER_KEY);
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
	__forceinline void CreateVertexAndIndexBuffer()
	{
		Mesh* pMesh = new Mesh();
		Resources::Insert<Mesh>(L"RectMesh", pMesh);
		pMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);
		// �ε��� ����
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
	}

	__forceinline void CreateMeterial() {

		// Default
		Material* pDefaultMaterial = new Material();
		pDefaultMaterial->SetShader(Resources::Find<Shader>(RECT_SHADER_KEY));
		Texture* pTexture = Resources::Load<Texture>(L"GennaroTexture", L"Gennaro.bmp");
		assert(pTexture != nullptr); 
		pDefaultMaterial->SetTexture(pTexture);


		Texture* pSpriteTexture = Resources::Load<Texture>(L"DefaultTexture", L"DefaultTexture.png");
		Resources::Insert<Material>(L"RectMaterial", pDefaultMaterial);

		Material* pSpriteMaterial = new Material();
		pSpriteMaterial->SetShader(Resources::Find<Shader>(SPRITE_SHADER_KEY));
		pSpriteMaterial->SetTexture(pSpriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", pSpriteMaterial);
	}

	void Initialize()
	{
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
		SetupInputLayout();
		CreateVertexAndIndexBuffer();
		CreateConstantBuffer();
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

}