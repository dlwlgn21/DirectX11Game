#pragma once
#include "jhResource.h"
#include "jhRenderer.h"

using namespace jh::graphics;
using namespace jh::renderer;

namespace jh
{
	class Shader;
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		HRESULT Load(const std::wstring& path) override;

		void SetDataAtConstantBuffer(eGPUPrameterType eGPUParamType, void* pData);
		void BindConstantBufferAndShader();

		__forceinline void SetShader(Shader* pShader)	{ assert(pShader != nullptr); mpShader = pShader; }
		__forceinline Shader* GetShader() const			{ return mpShader; }

	private:
		Shader* mpShader;
		renderer::MaterialConstantBuffer mMaterialConstantBuffer;
	};
}

