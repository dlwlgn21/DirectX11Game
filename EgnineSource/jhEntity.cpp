#include "jhEntity.h"

namespace jh
{
	Entity::Entity()
		: mID{reinterpret_cast<UINT32>(this)}
		, mName{}
	{
	}
	Entity::~Entity()
	{
	}
}