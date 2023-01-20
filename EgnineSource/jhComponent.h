#pragma once

namespace jh
{
	enum class eComponentType
	{
		NONE,
		TRANSFORM,
		CAMERA,

		// Render
		MESH,
		SKY_BOX,
		DECAL,

		SCRPIT,
		COUNT
	};

	class GameObject;
	class Component
	{
	public:
		friend class GameObject;

		Component(eComponentType eType);
		virtual ~Component();

		virtual void Initialize();
		virtual void Tick();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		const eComponentType meType;
		GameObject* mpOwner;
	};
}

