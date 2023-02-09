#pragma once

namespace jh
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();
	private:
		static Scene* mpPlayScene;
	};
}
