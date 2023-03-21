#pragma once
#include "jhScript.h"

namespace jh
{
	class BackgroundScript final : public Script
	{
	public:
		BackgroundScript();
		virtual ~BackgroundScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:
		const float		mSpeed;
		Vector2			mUVMove;
	};
}