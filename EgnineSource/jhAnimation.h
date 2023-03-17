#pragma once
#include "jhEntity.h"
#include "jhMath.h"
#include <functional>


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
			Vector2 LeftTop;				// 좌측 상단 좌표
			Vector2 Size;					// 좌측상단으로부터 잘라낼 가로세로 픽셀길이
			Vector2 Offset;		
			Vector2 AtlasSize;
			float	Duration;				// 프레임간 시간간격
			//std::function<void()> Event;	// 내가 원하는 스프라이트 번호에다가 이벤트 넣어놓음. 해당 스프라이트(인덱스)에서 실행 될 이벤트 함수

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
			UINT spriteCount,
			float duration,
			float magnification
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


