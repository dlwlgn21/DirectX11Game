#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Monster final : public GameObject
	{
	public:
		Monster();
		virtual ~Monster() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:
	};
}
