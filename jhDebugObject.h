#pragma once
#include "..\EgnineSource\jhGameObject.h"

namespace jh
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject() = default;

		void FixedUpdate() override;
	private:
	};
}

