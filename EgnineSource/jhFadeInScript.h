#pragma once
#include "jhScript.h"

namespace jh
{
	class FadeinScript final : public Script
	{
	public:
		FadeinScript();
		virtual ~FadeinScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:
		float mAccum;
		float mCoefficient;
	};
}