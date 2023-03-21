#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    float2 WorldPos : POSITION;
};


float4 main(VSOut _in) : SV_TARGET
{
    float time = fUVPosition.x;
    return float4(0.0f, 0.0f, 0.0f, time);
}