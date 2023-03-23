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

		void SetTarget(std::unique_ptr<Texture> pTextrue) { mspTargetTexture = std::move(pTextrue); }
	private:
		std::unique_ptr<Texture> mspTargetTexture;
	};
}