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

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

texture2D defaultTexture : register(t0);
