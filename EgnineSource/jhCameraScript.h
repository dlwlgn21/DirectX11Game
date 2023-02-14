#pragma once
#include "jhScript.h"

namespace jh
{
	class Transform;
	class CameraScript final : public Script
	{
	public:
		CameraScript();
		virtual ~CameraScript();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		Transform* mpTranform;
	};
}
