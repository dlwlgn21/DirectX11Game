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

	private:
		static Scene* mPlayScene;
	};
}
