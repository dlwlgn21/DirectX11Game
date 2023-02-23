#include "jhRendererComponent.h"

namespace jh
{
	RendererComponent::RendererComponent(const eComponentType eRendererType)
		: Component(eRendererType)
		, mpMaterial(nullptr)
		, mpMesh(nullptr)
	{

	}

}