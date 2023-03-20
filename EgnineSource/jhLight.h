#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"

using namespace jh::math;

namespace jh
{
	class Light : public Component
	{
	public:
		Light();
		virtual ~Light();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		__forceinline const graphics::LightAttribute& GetLightAttribute() const { return mLightAttribute; }

		void SetDiffuse(const Vector4 diffuse)			{ mLightAttribute.DiffuseLight = diffuse; }
		void SetAmbient(const Vector4 ambient)			{ mLightAttribute.AmbientLight = ambient; }
		void SetLightType(const eLightType eType)		{ mLightAttribute.ELightType = eType; }
		void SetRadius(const float radius)				{ mLightAttribute.Radius = radius;}
		void SetAngle(const float angle)				{ mLightAttribute.Angle = angle; }

		Vector4 GetDiffuse() const						{ return mLightAttribute.DiffuseLight; }
		eLightType GetLightType() const					{ return mLightAttribute.ELightType; }
		float GetRadius() const							{ return mLightAttribute.Radius; }
		float GetAngle() const							{ return mLightAttribute.Angle; }

	private:
		graphics::LightAttribute mLightAttribute;
	};
}

