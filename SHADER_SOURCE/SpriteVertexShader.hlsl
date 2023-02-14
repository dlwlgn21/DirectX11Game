#include "globals.hlsli"

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