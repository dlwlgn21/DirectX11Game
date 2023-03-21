#pragma once
#include "jhGraphics.h"
#include "jhResource.h"

namespace jh
{
	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		HRESULT Load(const std::wstring& path) override;
		bool CreateVertexBuffer(void* pData, const UINT count);
		bool CreateIndexBuffer(void* pData, const UINT count);

		void SetVertexAndIndexBufferAtIA();
		void Render();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>		mcpVertexBuffer;
		D3D11_BUFFER_DESC							mVertexBufferDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer>		mcpIndexBuffer;
		D3D11_BUFFER_DESC							mIndexBufferDesc;

		UINT										mIdxCount;
	};
}