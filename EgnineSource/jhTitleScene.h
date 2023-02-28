#pragma once
#include "jhScene.h"

namespace jh
{
	class TitleScene final : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

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
