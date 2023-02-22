#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};


struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : SV_Position;
};

float4 main(VSIn _in) : SV_POSITION
{
    VSOut output = (VSOut) 0.0f;
    
    float2 worldPos = float2(0.0f, 0.0f);
    worldPos.x = _in.Pos.x * fCameraScale.x * fResolution.x + fCameraPosition.x;
    worldPos.y = _in.Pos.y * fCameraScale.y * fResolution.y + fCameraPosition.y;
    
    const float meshScale = 1.0f;
    output.Pos = float4(_in.Pos.xy * meshScale, 0.9f, 1.0f);
    output.UV = _in.UV;
    output.WorldPos = worldPos;
    
	return pos;
}