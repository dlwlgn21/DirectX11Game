#pragma once
#include "jhScene.h"

namespace jh 
{
	class PlayScene final : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		void Initalize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void Release() override;

		void OnEnter() override;
		void OnExit() override;

	private:
	};
}

