#pragma once
#include "jhScript.h"

namespace jh
{
	class Transform;
	class PlayerScript final : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		Transform*		mpTranform;
	};
}

