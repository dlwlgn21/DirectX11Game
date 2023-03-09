#include "jhAnimation.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhTime.h"

constexpr const UINT MAX_SPRITE_SHEETS_COUNT = 16;
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

		// Ÿ�̸Ӱ� �ش� �������� �����ð����� ũ�� ���� �ε����� �̵�
		if (mSpriteSheets[mIndex].Duration < mAccumTimer)
		{
			mAccumTimer = 0.0f;
			++mIndex;
			if (mIndex >= mSpriteSheets.size())
			{
				mbIsAnimComplete = true;

				// �̰� �����̾߱�???? ����ڵ��� ��.
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
	void Animation::Create(const std::wstring& animKey, Texture* pAtalsImage, Vector2 leftTop, Vector2 size, Vector2 offset, UINT columnLength, UINT spriteLength, float duration)
	{
	}
	void Animation::BindAtShader()
	{
	}
	void Animation::ClearShaderTexture()
	{
	}
	void Animation::Reset()
	{
		mAccumTimer = 0.0f;
		mIndex = 0;
		mbIsAnimComplete = false;
	}
}