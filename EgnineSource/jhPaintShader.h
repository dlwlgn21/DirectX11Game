#include "jhComputeShader.h"
#include "jhTexture.h"

namespace jh
{
	class PaintShader final : public ComputeShader
	{
	public:
		PaintShader();
		virtual ~PaintShader() = default;

		void Bind() override;
		void Clear() override;

		void SetTarget(Texture* pTextrue) { assert(pTextrue != nullptr); mpTargetTexture = pTextrue; }
	private:
		Texture* mpTargetTexture;
	};
}