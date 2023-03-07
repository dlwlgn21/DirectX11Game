#include "jhDebugObject.h"

namespace jh
{
	DebugObject::DebugObject()
		: GameObject()
	{
	}

	void DebugObject::FixedUpdate()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent == nullptr)
				{continue;}
			pComponent->FixedUpdate();
		}
	}
}
