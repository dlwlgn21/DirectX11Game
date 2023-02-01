#pragma once
#include "jhComponent.h"

namespace jh
{
	class MeshRenderer final : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
	};
}

