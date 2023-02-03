#pragma once

namespace jh
{
	enum class eConstantBufferType
	{
		TRANSFORM,
		COUNT,
	};

	enum class eLayerType
	{
		NONE = 0,
		MONSTER, 
		PLAYER,
		COUNT = 16,
	};

	enum class eComponentType
	{
		NONE,
		TRANSFORM,								// ��ġ ������ �����ϴ� ������Ʈ
		CAMERA,
		MESH,
		MESH_RENDERER,
		COLLIDER,
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