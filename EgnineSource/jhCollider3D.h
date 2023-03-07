#pragma once
#include "jhComponent.h"

namespace jh
{
	class Collider3D : public Component
	{
	public:
		Collider3D();
		virtual ~Collider3D();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:

	};
}


