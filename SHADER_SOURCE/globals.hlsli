cbuffer Transform : register(b0)
{
    row_major matrix worldMat;
    row_major matrix viewMat;
    row_major matrix projectionMat;
}

cbuffer MaterialData : register(b1)
{
    int iData;
    float fData;
    float2 Xy;
    float3 Xyz;
    float4 Xyzw;
    Matrix mat;
}

cbuffer Grid : register(b2)
{
    float4 fCameraPosition;
    float2 fResolution;
    float2 fCameraScale;
}

cbuffer FadeOut : register(b3)
{
    float4 fDeltaTime;
}
cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasImageSize;
    uint   animationType;
}


SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

texture2D defaultTexture : register(t0);
//AtalsTexture
texture2D atlasTexture : register(t12);