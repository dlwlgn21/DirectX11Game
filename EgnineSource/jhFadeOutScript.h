#pragma once
#include "jhScript.h"

namespace jh
{
	class FadeoutScript final : public Script
	{
	public:
		FadeoutScript();
		virtual ~FadeoutScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:
		float mAccum;
		float mCoefficient;
	};
}