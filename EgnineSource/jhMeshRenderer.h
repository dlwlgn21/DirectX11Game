#pragma once
#include "jhComponent.h"

namespace jh
{
	class Mesh;
	class Material;
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
		void SetMaterial(Material* pMaterial) { assert(pMaterial != nullptr); mpMaterial = pMaterial; }

	private:
		Mesh*		mpMesh;
		Material*	mpMaterial;
	};
}

