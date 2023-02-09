#pragma once
#include "jhComponent.h"

namespace jh
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:

	};
}

