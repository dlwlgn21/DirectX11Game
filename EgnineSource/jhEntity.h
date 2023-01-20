#pragma once
#include "Engine.h"

namespace jh
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		__forceinline const std::wstring& GetName() { return mName; }
		__forceinline UINT32 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT32 mID;
	};
}