#pragma once
#include "Engine.h"

namespace jh
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring name) { mName = name; }
		std::wstring GetName() { return mName; }
		inline UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT32 mID;
	};
}