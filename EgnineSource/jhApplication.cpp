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
	}
	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();
		renderer::Initialize(); 
		SceneManager::Initalize();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}
	void Application::FixedUpdate()
	{
		SceneManager::FixedUpdate();
	}
	void Application::Render()
	{
		Time::Render(mHdc);
		mspGraphicDevice->ClearRenderTargetViewAndDepthStencilView();

		//SceneManager::Render();
		renderer::Render();
		mspGraphicDevice->Present();
	}

	void Application::Release()
	{
		SceneManager::Release();
		renderer::Release();
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