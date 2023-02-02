#include "jhRenderer.h"
#include "jhResources.h"


using namespace jh::graphics;
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
	ConstantBuffer* pConstantBuffers[static_cast<UINT>(eConstantBufferType::COUNT)] = {};

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

	__forceinline void CreateConstantBufferAndWriteAtGPU()
	{
		Vector4 pos(0.2f, 0.2f, 0.0f, 0.0f);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)] = new ConstantBuffer(eConstantBufferType::TRANSFORM);
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)]->CreateBuffer(sizeof(Vector4));
		pConstantBuffers[static_cast<UINT>(eConstantBufferType::TRANSFORM)]->WriteConstantBufferAtGPU(&pos);
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
		//cpConstantBuffer.Reset();
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
		for (int i = 0; i < static_cast<UINT>(eConstantBufferType::COUNT); ++i) 
		{
			if (pConstantBuffers[i] == nullptr)
			{
				continue;
			}
			delete pConstantBuffers[i];
			pConstantBuffers[i] = nullptr;
		}
	}

}