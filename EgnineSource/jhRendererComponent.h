#pragma once
#include "jhComponent.h"
#include "jhMaterial.h"
#include "jhMesh.h"

namespace jh
{
	class RendererComponent : public Component
	{
	public:
		RendererComponent(const eComponentType eRendererType);
		virtual ~RendererComponent() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		void SetMesh(Mesh* pMesh) { assert(pMesh != nullptr); mpMesh = pMesh; }
		void SetMaterial(Material* pMaterial) { assert(pMaterial != nullptr); mpMaterial = pMaterial; }

		Mesh* GetMesh() const { return mpMesh; }
		Material* GetMeterial() const { return mpMaterial; }
	protected:
		Mesh* mpMesh;
		Material* mpMaterial;
	};
}