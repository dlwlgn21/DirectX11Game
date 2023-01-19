#include "jhEntity.h"

namespace jh
{
	Entity::Entity()
		: mName{}
		, mID(reinterpret_cast<UINT32>(this))
	{
	}
	Entity::~Entity()
	{
	}
}