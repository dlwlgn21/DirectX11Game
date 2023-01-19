#include "jhGraphicDeviceDX11.h"
#include "jhMesh.h"
#include "jhRenderer.h"

namespace jh
{
	Mesh::Mesh()
		: mcpVertexBuffer(nullptr)
		, mVertexBufferDesc{}
		, mcpIndexBuffer(nullptr)
		, mIndexBufferDesc{}
		, mIdxCount(0)
	{
	}
	Mesh::~Mesh()
	{
	}
	HRESULT Mesh::Load(const std::wstring& path)
	{
		return S_OK;
	}
	bool Mesh::CreateVertexBuffer(void* pData, UINT count)
	{
		ZeroMemory(&mVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
		mVertexBufferDesc.ByteWidth = sizeof(renderer::Vertex) * count;
		mVertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		mVertexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subResourceData = {};
		subResourceData.pSysMem = pData;

		graphics::GetDevice()->CreateBuffer(
			&mVertexBufferDesc,
			&subResourceData,
			mcpVertexBuffer.ReleaseAndGetAddressOf()
		);

		return true;
	}
	bool Mesh::CreateIndexBuffer(void* pData, UINT count)
	{
		mIdxCount = count;
		ZeroMemory(&mIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
		mIndexBufferDesc.ByteWidth = sizeof(UINT) * count;
		mIndexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIndexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIndexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subResourceData = {};
		subResourceData.pSysMem = pData;
		graphics::GetDevice()->CreateBuffer(
			&mIndexBufferDesc,
			&subResourceData,
			mcpIndexBuffer.GetAddressOf()
		);
		return true;
	}
	void Mesh::SetVertexAndIndexBufferAtIA()
	{
		UINT stride = sizeof(renderer::Vertex);		// 하나의 버텍스 정보가 몇 바이트인지를 표시
		UINT offset = 0;							// 데이터의 첫번째 위치를 바이트로 지정

		graphics::GetDevice()->SetVertexBufferAtIA(0, 1, mcpVertexBuffer.GetAddressOf(), &stride, &offset);
		graphics::GetDevice()->SetIndexBufferAtIA(mcpIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void Mesh::Render()
	{
		graphics::GetDevice()->DrawIndexed(mIdxCount, 0, 0);
	}
}