#pragma once
#include "jhRendererComponent.h"

namespace jh
{
	class ParticleSystem final : public RendererComponent
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


	private:
		class graphics::StructuredBuffer* mpStructuredBuffer;
		UINT		mParticleCount;
		Vector4		mStartSize;
		Vector4		mEndSize;
		Vector4		mStartColor;
		Vector4		mEndColor;
		float		mStartLifeTime;

	};
}