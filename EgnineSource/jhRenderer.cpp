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
	// 버텍스 버퍼
	// 상수 버퍼
	Microsoft::WRL::ComPtr<ID3D11Buffer>			cpConstantBuffer;


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

	__forceinline void LoadAndSetShader()
	{
		pShader = new Shader();
		pShader->Create(graphics::eShaderStage::VERTEX_SHADER, L"TriangleVS.hlsl", "VS_Test");
		pShader->Create(graphics::eShaderStage::PIXEL_SHADER, L"TrianglePS.hlsl", "PS_Test");

		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};
		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		HRESULT hr = graphics::GetDevice()->GetID3D11Device()->CreateInputLayout(
			arrLayout,
			2,
			pShader->GetVertexShaderBlob(),
			pShader->GetVertexShaderBufferSize(),
			pShader->GetInputLayoutAddressOf()
		);
		ifFailed(hr);
		graphics::GetDevice()->GetContext()->IASetInputLayout(pShader->GetInputLayout());

	}

	__forceinline void SetupInputLayout()
	{

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
		CreateVertexBuffer();
		CreateIndexBuffer();
		LoadAndSetShader();
		SetupInputLayout();
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