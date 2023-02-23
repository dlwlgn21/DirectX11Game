#pragma once
#include "jhScript.h"
#include "jhCamera.h"

namespace jh
{
	class GridScript final : public Script
	{
	public:
		GridScript();
		virtual ~GridScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		__forceinline void SetCamera(Camera* pCamera)		{ assert(pCamera != nullptr); mpCamera = pCamera; }
	private:
		Camera* mpCamera;
	};
}

