#pragma once
#include "jhComponent.h"

namespace jh
{
	class Animation;
	class Animator : public Component
	{
	public:
		struct Events
		{

		};
	private:
		std::unordered_map<std::wstring, Animation*>	mAnimationMap;
		std::unordered_map<std::wstring, Events*>		mEventMap;
	};
}



