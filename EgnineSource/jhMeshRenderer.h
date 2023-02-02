#pragma once
#include "jhComponent.h"

namespace jh
{
	class Mesh;
	class Shader;
	class MeshRenderer final : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetMesh(Mesh* pMesh) { assert(pMesh != nullptr); mpMesh = pMesh; }
		void SetShader(Shader* pShader) { assert(pShader != nullptr); mpShader = pShader; }

	private:
		Mesh*		mpMesh;
		Shader*		mpShader;
	};
}

