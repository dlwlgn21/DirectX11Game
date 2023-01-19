#include "jhResources.h"

namespace jh
{
	std::unordered_map<std::wstring, std::unique_ptr<Resource>> Resources::mResources;
}