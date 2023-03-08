#include "jhGridScript.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhApplication.h"
#include "jhConstantBuffer.h"
#include "jhRenderer.h"
#include "jhSceneManager.h"

namespace jh
{
	GridScript::GridScript()
		: Script()
		, mpCamera(nullptr)
	{

	}
	
	void GridScript::Initialize()
	{
	}
	void GridScript::Update()
	{
	}
	void GridScript::FixedUpdate()
	{
		if (mpCamera == nullptr)
		{
			return;
		}

		GameObject* pGameObj = mpCamera->GetOwner();
		Transform* pTransform = static_cast<Transform*>(pGameObj->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(pTransform != nullptr);

		Vector3 cameraPos = pTransform->GetPosition();
		Vector4 v4CameraPos(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mpCamera->GetScale();

		RECT winRect{};
		GetClientRect(Application::GetInstance().GetHwnd(), &winRect);
		float width = static_cast<float>(winRect.right - winRect.left);
		float height = static_cast<float>(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// ConstantBuffer
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::GRID)];
		assert(pConstantBuffer != nullptr);
		renderer::GridConstantBuffer data;
		data.fCameraPosition = v4CameraPos;
		data.fCameraScale = Vector2(scale, scale);
		data.fResolution = resolution;

		pConstantBuffer->WriteConstantBufferAtGPU(&data);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
	}
	void GridScript::Render()
	{

	}

}