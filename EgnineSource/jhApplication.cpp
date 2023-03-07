#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhSceneManager.h"

namespace jh
{
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
		Destroy();
	}
	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();
		renderer::Initialize(); 
		SceneManager::GetInatance().Initalize();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::GetInatance().Update();
	}
	void Application::FixedUpdate()
	{
		SceneManager::GetInatance().FixedUpdate();
	}
	void Application::Render()
	{
		Time::Render(mHdc);
		mspGraphicDevice->ClearRenderTargetViewAndDepthStencilView();

		//SceneManager::Render();
		renderer::Render();
	}

	void Application::Destroy()
	{
	}

	void Application::Release()
	{
		SceneManager::GetInatance().Release();
		renderer::Release();
	}

	void Application::Present()
	{
		mspGraphicDevice->Present();
	}

	void Application::SetWindowAndGraphicDevice(HWND hwnd, UINT width, UINT height)
	{
		if (mspGraphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;
			assert(mHwnd != nullptr);
			mHdc = GetDC(mHwnd);
			graphics::eValidationMode eValidateMod = graphics::eValidationMode::DISABLED;
			mspGraphicDevice = std::make_unique<graphics::GraphicDevice_DX11>(eValidateMod);
			graphics::GetDevice() = mspGraphicDevice.get();

		}

		RECT rt = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}