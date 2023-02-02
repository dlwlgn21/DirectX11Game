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
		TRANSFORM,								// 위치 데이터 수정하는 컴포넌트
		CAMERA,
		MESH,
		MESH_RENDERER,
		COLLIDER,
		UI,
		SCRIPT,
		COUNT
	};

}