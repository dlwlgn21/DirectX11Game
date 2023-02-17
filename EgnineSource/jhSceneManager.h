#pragma once
#include "jhScene.h"

namespace jh
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();
		static Scene* GetCurrentScene() { return mpPlayScene; }
	private:
		static Scene* mpPlayScene;
	};
}
