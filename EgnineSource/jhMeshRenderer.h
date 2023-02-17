#pragma once
#include "jhRendererComponent.h"

namespace jh
{
	class MeshRenderer final : public RendererComponent
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	};
}

