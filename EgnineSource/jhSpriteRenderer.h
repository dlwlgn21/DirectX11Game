#pragma once
#include "jhComponent.h"

namespace jh
{
	class Mesh;
	class Material;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetMesh(Mesh* pMesh) { assert(pMesh != nullptr); mpMesh = pMesh; }
		void SetMaterial(Material* pMaterial) { assert(pMaterial != nullptr); mpMaterial = pMaterial; }

	private:
		Mesh* mpMesh;
		Material* mpMaterial;
	};
}

