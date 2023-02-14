#include "jhCameraScript.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mpTranform(nullptr)
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos.z += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos.z -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos.x += 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos.y -= 3.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos.y += 3.0f * Time::DeltaTime();
		}

		mpTranform->SetPosition(pos);
	}
	void CameraScript::FixedUpdate()
	{
	}
	void CameraScript::Render()
	{
	}
}