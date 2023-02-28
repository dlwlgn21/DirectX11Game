#pragma once
#include "jhScene.h"

namespace jh
{
	class GameObject;
	class SceneManager final
	{
	public:
		static SceneManager& GetInatance()
		{
			static SceneManager manager;
			return manager;
		}
		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;

		void Initalize();
		void Update();
		void FixedUpdate();
		void Render();
		void Destroy();
		void Release();
		void LoadScene(eSceneType eType);
		Scene* GetCurrentScene() { return mpPlayScene; }


	private:
		~SceneManager() = default;
		SceneManager()
			: mpPlayScene(nullptr)
		{
			mScenes.reserve(static_cast<UINT>(eSceneType::COUNT));
			mScenes.resize(static_cast<UINT>(eSceneType::COUNT));
		}


	private:
		std::vector<Scene*> mScenes;
		Scene* mpPlayScene;
	};
}
