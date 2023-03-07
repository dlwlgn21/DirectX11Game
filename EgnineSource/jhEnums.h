#pragma once

namespace jh
{
	enum class eLayerType
	{
		NONE = 0,
		CAMERA,
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
		TRANSFORM,								// 위치 데이터 수정하는 컴포넌트
		CAMERA,
		MESH,
		COLLIDER,
		MESH_RENDERER,
		SPRITE_RENDERER,
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

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};
}