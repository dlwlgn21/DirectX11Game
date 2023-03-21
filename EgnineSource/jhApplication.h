#pragma once
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	class Application final
	{
	public:
		static Application& GetInstance()
		{
			static Application instance;
			return instance;
		}

		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;
		void Initialize();

		// Running main engine loop
		void Run();
		// 게임 로직, 캐릭터 이동 등등
		void Update();
		// CPU Update
		void FixedUpdate();
		// GPU Update
		void Render();

		void Destroy();

		void Release();
		
		void Present();

		void SetWindowAndGraphicDevice(HWND hwnd, const UINT width, const UINT height);
		HWND GetHwnd() const { return mHwnd; }
		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }

	private:
		Application()
			: mspGraphicDevice(nullptr)
			, mHwnd(NULL)
			, mHdc(NULL)
			, mWidth(0)
			, mHeight(0)
			, mbIsInitialize(false)
		{
		}
	public:
		~Application() = default;

	private:
		std::unique_ptr<graphics::GraphicDevice_DX11> mspGraphicDevice;
		HWND mHwnd;
		HDC	 mHdc;
		UINT mWidth;
		UINT mHeight;
		bool mbIsInitialize;
	};
}

