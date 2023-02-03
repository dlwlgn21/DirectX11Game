#include "jhTexture.h"

namespace jh
{
	Texture::Texture()
		: Resource(eResourceType::TEXTURE)
		, mTextureDesc{}
	{
	}
	Texture::~Texture()
	{
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

	void Texture::SetShaderResourceView(graphics::eShaderStage shaderStage, UINT slot)
	{
		graphics::GetDevice()->SetShaderResourceView(shaderStage, slot, mcpShaderResourceView.GetAddressOf());
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