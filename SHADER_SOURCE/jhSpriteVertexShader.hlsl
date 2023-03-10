#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VSOut main(VSIn _in)
{
    VSOut output = (VSOut) 0.f;
    
    float4 worldPos = mul(_in.Pos, worldMat);
    float4 viewPos = mul(worldPos, viewMat);
    float4 projectionPos = mul(viewPos, projectionMat);
    
    output.Pos = projectionPos;
    output.Color = _in.Color;
    output.UV = _in.UV;
    return output;
}