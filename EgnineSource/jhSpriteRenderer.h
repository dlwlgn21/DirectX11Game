#pragma once
#include "jhRendererComponent.h"

namespace jh
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	};
}

