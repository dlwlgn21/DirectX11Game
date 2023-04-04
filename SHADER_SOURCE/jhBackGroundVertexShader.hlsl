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
    VSOut output = (VSOut) 0.0f;
    const float MESH_SCALE = 2.0f;
    
    //float2 worldPos = float2(_in.Pos.x * MESH_SCALE, _in.Pos.y * MESH_SCALE);
    
    //worldPos.x = _in.Pos.x * fCameraScale.x * fResolution.x + fCameraPosition.x;
    //worldPos.y = _in.Pos.y * fCameraScale.y * fResolution.y + fCameraPosition.y;
    float4 worldPos = mul(_in.Pos, worldMat);
    float4 viewPos = mul(worldPos, viewMat);
    float4 projectionPos = mul(viewPos, projectionMat);
    
    //output.Pos = projectionPos;
    //output.Color = _in.Color;
    //output.UV = _in.UV;
    
    output.Pos = float4(worldPos.xy * MESH_SCALE, 10.0f, 1.0f);
    output.UV = _in.UV;
    
    return output;
}