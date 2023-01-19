#include "jhApplication.h"
//#include "jhRenderer.h"
//#include "jhTime.h"


namespace jh
{
	void Application::Run()
	{
		Tick();
		FixedUpdate();
		Render();
	}
	void Application::Initialize()
	{
		//Time::Initialize();
		//renderer::Initialize();
	}
	void Application::Tick()
	{
		//Time::Tick();
	}
	void Application::FixedUpdate()
	{
	}
	void Application::Render()
	{
		//mspGraphicDevice->Draw();
		//Time::Render(mHdc);
	}
	//void Application::SetWindowAndGraphicDevice(HWND hwnd, UINT width, UINT height)
	//{
	////	if (mspGraphicDevice == nullptr)
	////	{
	////		mHwnd = hwnd;
	////		mWidth = width;
	////		mHeight = height;
	////		assert(mHwnd != nullptr);
	////		mHdc = GetDC(mHwnd);
	////		graphics::eValidationMode eValidateMod = graphics::eValidationMode::DISABLED;
	////		mspGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>(eValidateMod);
	////		graphics::GetDevice() = mspGraphicDevice.get();

	////	}

	////	RECT rt = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	////	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	////	SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	////	ShowWindow(mHwnd, true);
	////	UpdateWindow(mHwnd);
	//}
}