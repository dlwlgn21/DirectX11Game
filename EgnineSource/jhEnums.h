#pragma once

namespace jh
{
	enum class eLayerType
	{
		NONE = 0,
		CAMERA,
		BACKGROUND,
		GRID,
		MONSTER, 
		PLAYER,


		UI,
		COUNT = 16,
	};

	enum class eSceneType
	{
		TITLE,
		PLAY,
		ENDING,
		COUNT
	};
	enum class eComponentType
	{
		NONE,
		TRANSFORM,
		CAMERA,
		MESH,
		COLLIDER,
		MESH_RENDERER,
		SPRITE_RENDERER,
		ANIMATOR,
		PARTICLE_SYSTEM,
		LIGHT,
		UI,
		SCRIPT,
		COUNT
	};

	enum class eResourceType
	{
		MESH,
		TEXTURE,
		METERIAL,
		SOUND,
		PREFAB,
		MESH_DATA,
		GRAPHIC_SHADER,
		COMPUTE_SHADER,
		SCRPIT,
		COUNT
	};

	enum class eColliderType
	{
		NONE,
		RECT,
		CIRCLE,
		BOX,
		SPHERE,
		COUNT
	};

	enum class eLightType
	{
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
		COUNT
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};
}