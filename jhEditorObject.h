#pragma once
#include "..\EgnineSource\jhGameObject.h"

namespace jh
{
	class EditorObject : public GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject() = default;

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	private:
	};
}
