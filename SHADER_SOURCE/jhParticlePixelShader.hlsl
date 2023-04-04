#include "globals.hlsli"

struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

float4 main(GSOutput _In) : SV_TARGET
{
    float4 outColor = (float4) 0.0f;
    //outColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
    outColor = defaultTexture.Sample(pointSampler, _In.UV);
    return outColor;
}