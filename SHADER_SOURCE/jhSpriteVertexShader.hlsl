#include "globals.hlsli"
struct VSIn
{
    float4 Pos      : POSITION;
    float4 Color    : COLOR;
    float2 UV       : TEXCOORD;
};

struct VSOut
{
    float4 Pos      : SV_POSITION;
    float3 WolrdPos : POSITION;                 // PS에서 라이팅 계산하기 위해 보내주는 정보.
    float4 Color    : COLOR;
    float2 UV       : TEXCOORD;
};

VSOut main(VSIn _in)
{
    VSOut output = (VSOut) 0.f;
    
    float4 worldPos = mul(_in.Pos, worldMat);
    float4 viewPos = mul(worldPos, viewMat);
    float4 projectionPos = mul(viewPos, projectionMat);
    
    output.Pos = projectionPos;
    output.WolrdPos = float3(worldPos.x, worldPos.y, worldPos.z);
    output.Color = _in.Color;
    _in.UV.x = 1 - _in.UV.x;
    output.UV = _in.UV;
    return output;
}