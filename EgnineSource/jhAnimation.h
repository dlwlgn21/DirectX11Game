#pragma once
#include "jhEntity.h"
#include "jhMath.h"


using namespace jh::math;
namespace jh
{
	class Animator;
	class Texture;
	class Animation : public Entity
	{
	public:
		Animation();
		virtual ~Animation();

		struct Sprite
		{
			Vector2 LeftTop;	// ���� ��� ��ǥ
			Vector2 Size;		// ����������κ��� �߶� ���μ��� �ȼ�����
			Vector2 Offset;		
			Vector2 AtlasSize;
			float	Duration;	// �����Ӱ� �ð�����
			Sprite()
				: LeftTop(Vector2::Zero)
				, Size(Vector2::Zero)
				, Offset(Vector2::Zero)
				, AtlasSize(Vector2::Zero)
				, Duration(0.0f)
			{
			}
		};

		void Update();
		void FixedUpdate();
		void Render();

		void Create(
			const std::wstring& animKey,
			Texture* pAtalsImage,
			Vector2 leftTop, 
			Vector2 size, 
			Vector2 offset, 
			UINT columnLength,
			UINT spriteLength,
			float duration
		);
		void BindAtShader();
		void ClearShaderTexture();
		void Reset();

		__forceinline bool IsAnimComplete() const { return mbIsAnimComplete; }
		const std::wstring& GetAnimationKey() { return mAnimKey; }

	private:
		std::wstring			mAnimKey;
		Animator*				mpAnimator;
		Texture*				mpAtlasImage;
		std::vector<Sprite>		mSpriteSheets;
		UINT					mIndex;
		float					mAccumTimer;
		bool					mbIsAnimComplete;

	};
}


