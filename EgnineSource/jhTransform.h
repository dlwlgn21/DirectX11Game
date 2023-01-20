#pragma once
#include "jhComponent.h"

namespace jh
{
	class Transform final : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		void Initialize() override;
		void Tick() override;
		void FixedUpdate() override;
		void Render() override;
	private:

	};
}
