#pragma once

namespace jh
{
	enum class eLayerType
	{
		NONE = 0,
		MONSTER, 
		PLAYER,
		CAMERA,
		COUNT = 16,
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
}