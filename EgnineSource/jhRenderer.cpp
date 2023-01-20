#include "jhRenderer.h"
#include "jhResources.h"

namespace jh::renderer
{

	Vertex vertices[VERTEX_COUNT] =
	{
		{ -0.5f,	0.5f,		0.0f,	{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ 0.5f,		0.5f,		0.0f,	{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f,		-0.5f,		0.0f,	{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ -0.5f,	-0.5f,		0.0f,	{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	Mesh* pMesh = nullptr;
	Shader* pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			cpConstantBuffer;





	__forceinline void LoadAndSetShader()
	{
		pShader = new Shader();
		pShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"jhVertexShader.hlsl", "VS_Test");
		pShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"jhPixelShader.hlsl", "PS_Test");
	}

	__forceinline void SetupInputLayout()
	{
		D3D11_INPUT_ELEMENT_DESC inputDesc[2] = {};
		inputDesc[0].AlignedByteOffset =			0;
		inputDesc[0].Format =						DXGI_FORMAT_R32G32B32_FLOAT;
		inputDesc[0].InputSlot =					0;
		inputDesc[0].InputSlotClass =				D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[0].SemanticName =					"POSITION";
		inputDesc[0].SemanticIndex =				0;

		inputDesc[1].AlignedByteOffset =			12;
		inputDesc[1].Format =						DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputDesc[1].InputSlot =					0;
		inputDesc[1].InputSlotClass =				D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[1].SemanticName =					"COLOR";
		inputDesc[1].SemanticIndex =				0;

		graphics::GetDevice()->CreateInputLayout(
			inputDesc,
			2,
			pShader->GetVertexShaderBlob(),
			pShader->GetVertexShaderBlobSize(),
			pShader->GetInputLayoutAddressOf()
		);
	}
	__forceinline void CreateVertexBuffer()
	{
		pMesh = new Mesh();
		Resources::Insert<Mesh>(L"RectMesh", pMesh);
		pMesh->CreateVertexBuffer(vertices, VERTEX_COUNT);
	}
	__forceinline void CreateIndexBuffer()
	{
		// 인덱스 버퍼
		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		pMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
	}

	__forceinline void CreateConstantBufferAndWriteAtGPU()
	{
		// 상수 버퍼
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constantBufferDesc.ByteWidth = sizeof(Vector4);
		constantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		graphics::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, cpConstantBuffer.ReleaseAndGetAddressOf());

		Vector4 pos(0.2f, 0.2f, 0.0f, 0.0f);
		graphics::GetDevice()->WriteConstantBufferAtGPU(cpConstantBuffer.Get(), &pos, sizeof(Vector4));
	}

	void Initialize()
	{
		LoadAndSetShader();
		SetupInputLayout();
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateConstantBufferAndWriteAtGPU();
	}
	void Release()
	{
		cpConstantBuffer.Reset();
		//cpIndexBuffer.Reset();
		//cpVertexBuffer.Reset();
		//if (pMesh != nullptr)
		//{
		//	delete pMesh;
		//}
		//pMesh = nullptr;

		if (pShader)
		{
			delete pShader;
		}
	}

}