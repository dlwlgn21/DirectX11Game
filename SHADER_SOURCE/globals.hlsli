struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

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

SamplerState pointSampler : register(s0);
SamplerState linearSampler : register(s1);
SamplerState anisotropicSampler : register(s2);

texture2D defaultTexture : register(t0);
