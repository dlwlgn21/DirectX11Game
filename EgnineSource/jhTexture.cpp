#include "jhTexture.h"

using namespace jh::graphics;

namespace jh
{
	Texture::Texture()
		: Resource(eResourceType::TEXTURE)
		, mTextureDesc{}
		, mcpTexture(nullptr)
		, mcpShaderResourceView(nullptr)
		, mcpDepthStencilView(nullptr)
		, mcpRenderTargetView(nullptr)
		, mcpUnorderedAccessView(nullptr)
	{
	}
	Texture::~Texture()
	{
		mcpTexture.Reset();
		mcpShaderResourceView.Reset();
		mcpDepthStencilView.Reset();
		mcpRenderTargetView.Reset();
		mcpUnorderedAccessView.Reset();
	}

	void Texture::Clear(const UINT startSlot)
	{
		ID3D11ShaderResourceView* pSrv = nullptr;
		graphics::GetDevice()->SetShaderResourceView(eShaderStage::VERTEX_SHADER, startSlot, &pSrv);
		graphics::GetDevice()->SetShaderResourceView(eShaderStage::PIXEL_SHADER, startSlot, &pSrv);
		graphics::GetDevice()->SetShaderResourceView(eShaderStage::COMPUTE_SHADER, startSlot, &pSrv);
	}

	HRESULT Texture::Load(const std::wstring& fileName)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += L"\\Resources\\" + fileName;


		const UINT MAX_LENGTH = 256;
		wchar_t szExtension[MAX_LENGTH] = {};
		if (_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, MAX_LENGTH) != 0)
		{
			// FAILED _wsplitpath_s
			assert(false);
		}

		std::wstring extension(szExtension);

 		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		createShaderResourceView();
		
		return S_OK;
	}

	bool Texture::Create(const UINT width, const UINT height, const DXGI_FORMAT format, const UINT bindFlag)
	{
		//Depth stencil texture
		mTextureDesc.BindFlags = bindFlag;
		mTextureDesc.Usage = D3D11_USAGE_DEFAULT;
		mTextureDesc.CPUAccessFlags = 0;
		mTextureDesc.Format = format;
		mTextureDesc.Width = width;
		mTextureDesc.Height = height;
		mTextureDesc.ArraySize = 1;

		mTextureDesc.SampleDesc.Count = 1;
		mTextureDesc.SampleDesc.Quality = 0;

		mTextureDesc.MipLevels = 0;
		mTextureDesc.MiscFlags = 0;

		if (!GetDevice()->CreateTexture(&mTextureDesc, mcpTexture.GetAddressOf()))
			return false;

		if (bindFlag & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(mcpTexture.Get(), nullptr, mcpDepthStencilView.GetAddressOf()))
			{
				assert(false);
				return false;
			}
		}

		if (bindFlag & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(mcpTexture.Get(), nullptr, mcpShaderResourceView.GetAddressOf()))
			{
				assert(false);
				return false;
			}
		}

		if (bindFlag & D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = format;
			tUAVDesc.Texture2D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnorderedAccessView(mcpTexture.Get(), nullptr, mcpUnorderedAccessView.GetAddressOf()))
			{
				assert(false);
				return false;
			}
		}

		return true;
	}

	void Texture::SetShaderResourceView(const graphics::eShaderStage shaderStage, const UINT slot)
	{
		graphics::GetDevice()->SetShaderResourceView(shaderStage, slot, mcpShaderResourceView.GetAddressOf());
	}

	void Texture::Clear()
	{
		ID3D11ShaderResourceView* pSrv = nullptr;
		graphics::GetDevice()->SetShaderResourceView(eShaderStage::VERTEX_SHADER, 0, &pSrv);
		graphics::GetDevice()->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0, &pSrv);
		//graphics::GetDevice()->SetShaderResourceView(eShaderStage::DOMAIN_SHADER, 0, mcpShaderResourceView.GetAddressOf());
		//graphics::GetDevice()->SetShaderResourceView(eShaderStage::GEOMETRY_SHADER, 0, mcpShaderResourceView.GetAddressOf());
		//graphics::GetDevice()->SetShaderResourceView(eShaderStage::HULL_SHADER, 0, mcpShaderResourceView.GetAddressOf());
		//graphics::GetDevice()->SetShaderResourceView(eShaderStage::CS, 0, mcpShaderResourceView.GetAddressOf());
	}

	void Texture::SetUnorderdAccessView(const UINT startSlot)
	{
		UINT initValue = -1;
		graphics::GetDevice()->SetUnorderedAccessView(startSlot, 1, mcpUnorderedAccessView.GetAddressOf(), &initValue);
	}
	void Texture::ClearUnorderdAccessView(const UINT startSlot)
	{
		ID3D11UnorderedAccessView* pNull = nullptr;
		UINT initValue = -1;
		graphics::GetDevice()->SetUnorderedAccessView(startSlot, 1, &pNull, &initValue);
	}


	void Texture::createShaderResourceView()
	{
		HRESULT hr = CreateShaderResourceView(
			graphics::GetDevice()->GetID3D11Device(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mImage.GetMetadata(),
			mcpShaderResourceView.ReleaseAndGetAddressOf()
		);

		if (FAILED(hr))
		{
			assert(false);
		}

		// TODO : 이거 에러 일으킬 수 있음. reinterpret_cast 때문.
		mcpShaderResourceView->GetResource(reinterpret_cast<ID3D11Resource**>(mcpTexture.GetAddressOf()));
	}
}