#include "jhAnimation.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhTime.h"
#include "jhRenderer.h"

constexpr const UINT MAX_SPRITE_SHEETS_COUNT = 16;
constexpr const UINT ATLAS_TEXTURE_SLOT_NUMBER = 12;
namespace jh
{
	Animation::Animation()
		: mpAnimator(nullptr)
		, mAnimKey()
		, mpAtlasImage(nullptr)
		, mIndex(0)
		, mAccumTimer(0.0f)
		, mbIsAnimComplete(false)
	{
		mSpriteSheets.reserve(MAX_SPRITE_SHEETS_COUNT);
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
		if (mbIsAnimComplete)
			{return;}
		mAccumTimer += Time::DeltaTime();

		// 타이머가 해당 프레임의 유지시간보다 크면 다음 인덱스로 이동
		if (mAccumTimer >= mSpriteSheets[mIndex].Duration)
		{
			mAccumTimer = 0.0f;
			++mIndex;
			if (mIndex >= mSpriteSheets.size())
			{
				mbIsAnimComplete = true;

				// 이게 무슨이야기???? 방어코드라고 함.
				mIndex = static_cast<UINT>(mSpriteSheets.size() - 1);
			}

		}

	}
	void Animation::FixedUpdate()
	{
	}
	void Animation::Render()
	{
	}
	void Animation::Create(const std::wstring& animKey, Texture* pAtalsImage, Vector2 leftTop, Vector2 seperatingSize, Vector2 offset, UINT spriteCount, float duration, float magnification)
	{
		assert(pAtalsImage != nullptr);
		mpAtlasImage = pAtalsImage;
		mAnimKey = animKey;
		float width = static_cast<float>(pAtalsImage->GetWidth());
		float height = static_cast<float>(pAtalsImage->GetHeight());
		for (UINT i = 0; i < spriteCount; ++i)
		{
			Sprite sprite;
			// // 텍스처 좌표는 정규화된 좌표니까 0~1사이의 값으로 바꾸어 주어야 함
			sprite.LeftTop = Vector2((leftTop.x + (seperatingSize.x * i)) / width, leftTop.y / height);
			sprite.Size = Vector2(seperatingSize.x / width, seperatingSize.y / height);
			sprite.Offset = offset;
			sprite.Duration = duration;
			sprite.AtlasSize = Vector2(magnification / width, magnification / height);					// PixelShader에서 아틀라스의 크기를 알게 하기 위해서 넣어주는 값
			mSpriteSheets.push_back(sprite);
		}
	}
	void Animation::BindAtShader()
	{
		assert(mpAtlasImage != nullptr);
		mpAtlasImage->SetShaderResourceView(graphics::eShaderStage::PIXEL_SHADER, ATLAS_TEXTURE_SLOT_NUMBER);
		ConstantBuffer* pAnimConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::ANIMATION)];
		assert(pAnimConstantBuffer != nullptr);
		renderer::AnimationConstantBuffer animConstantBuffer;
		ZeroMemory(&animConstantBuffer, sizeof(renderer::AnimationConstantBuffer));
		animConstantBuffer.AnimationType = static_cast<UINT>(eAnimatnionType::SECOND_DIMENTION);
		animConstantBuffer.LeftTop = mSpriteSheets[mIndex].LeftTop;
		animConstantBuffer.Offset = mSpriteSheets[mIndex].Offset;
		animConstantBuffer.Size = mSpriteSheets[mIndex].Size;
		animConstantBuffer.AtlasImageSize = mSpriteSheets[mIndex].AtlasSize;
		pAnimConstantBuffer->WriteConstantBufferAtGPU(&animConstantBuffer);
		pAnimConstantBuffer->SetConstantBufferAtShader(graphics::eShaderStage::PIXEL_SHADER);
	}
	void Animation::ClearShaderTexture()
	{
		Texture::Clear(ATLAS_TEXTURE_SLOT_NUMBER);
		// Texture Clear
		ConstantBuffer* pAnimConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::ANIMATION)];
		assert(pAnimConstantBuffer != nullptr);
		renderer::AnimationConstantBuffer animationConstantBuffer = {};
		animationConstantBuffer.AnimationType = static_cast<UINT>(eAnimatnionType::NO_ANIMATION);
		pAnimConstantBuffer->WriteConstantBufferAtGPU(&animationConstantBuffer);
		pAnimConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
	void Animation::Reset()
	{
		mAccumTimer = 0.0f;
		mIndex = 0;
		mbIsAnimComplete = false;
	}
}