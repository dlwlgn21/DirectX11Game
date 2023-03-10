#pragma once
#include "jhEntity.h"

namespace jh
{
	class Resource : public Entity
	{
	public:
		Resource(const eResourceType eType);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }


	protected:
		std::wstring mPath;
		std::wstring mKey;
		const eResourceType meType;
	};
}
