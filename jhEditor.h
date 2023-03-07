#pragma once
#include "jhDebugObject.h"
#include "jhWidget.h"
#include "jhEditorObject.h"
#include "EgnineSource/jhGraphics.h"

namespace jh
{
	class Editor final
	{
	public:
		Editor(const Editor& other) = delete;
		Editor& operator=(const Editor& other) = delete;

		static Editor& GetInstance()
		{
			static Editor instance;
			return instance;
		}

		void Run();
		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();
		void DebugRender(graphics::DebugMesh& mesh);
		void Destroy();
		void Release();

	private:
		Editor() = default;
		~Editor() = default;

	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;
	};
}

