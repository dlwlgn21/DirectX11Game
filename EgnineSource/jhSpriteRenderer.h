#pragma once
#include "jhRendererComponent.h"

namespace jh
{
	class SpriteRenderer : public RendererComponent
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	};
}

