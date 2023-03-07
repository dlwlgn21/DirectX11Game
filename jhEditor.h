#pragma once
#include "Editor_Source/jhDebugObject.h"
#include "Editor_Source/jhWidget.h"
#include "Editor_Source/jhEditorObject.h"

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
		void DebugRender();
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

