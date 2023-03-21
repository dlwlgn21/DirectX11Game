#include "jhComponent.h"
#include "jhGameObject.h"

namespace jh
{
	Component::Component(const eComponentType eType)
		: meType(eType)
		, mpOwner(nullptr)
	{
	}
}