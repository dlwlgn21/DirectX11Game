#include "Light.hlsli"

cbuffer Transform : register(b0)
{
    row_major matrix worldMat;
    row_major matrix viewMat;
    row_major matrix projectionMat;
}

cbuffer MaterialData : register(b1)
{
    float fData;
}

cbuffer Grid : register(b2)
{
    float4 fCameraPosition;
    float2 fResolution;
    float2 fCameraScale;
}

cbuffer TranslateBuffer : register(b3)
{
    float4 fUVPosition;
}
cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasImageSize;
    uint   animationType;
    uint   isFlip;

}

cbuffer NumberOfLight : register(b5)
{
    uint NumberOfLight;
}

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

texture2D defaultTexture : register(t0);
//AtalsTexture
texture2D atlasTexture : register(t12);

StructuredBuffer<LightAttribute> lightAttributes : register(t13);

void CalculateLight(in out LightColor pLightColor, float3 worldPosition, uint idx)
{
    
    /*
    	DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT,
    */
    const int DIRECTIONAL_LIGHT = 0;
    const int POINT_LIGHT = 1;
    const int SPOT_LIGHT = 2;
    if (lightAttributes[idx].Type == DIRECTIONAL_LIGHT)
    {
        pLightColor.Diffuse += lightAttributes[idx].Color.Diffuse;
    }
    else if (lightAttributes[idx].Type == POINT_LIGHT)
    {
        float length = distance(lightAttributes[idx].Position.xy, worldPosition.xy);
        if (length < lightAttributes[idx].Radius)
        {
            // 빛이 범위 안이라면
            float ratio = 1.0f - (length / lightAttributes[idx].Radius);
            pLightColor.Diffuse += (lightAttributes[idx].Color.Diffuse * ratio);
        }

    }
    else
    {
        // 3D에서 추가될 부분
    }
    //pLightColor.Diffuse += lightAttributes[0].Color.Diffuse;

    
}