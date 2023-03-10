#include "globals.hlsli"
float4 main(float4 pos : POSITION) : SV_Position
{
    
    float4 worldPos = mul(pos, worldMat);
    float4 viewPos = mul(worldPos, viewMat);
    float4 projectionPos = mul(viewPos, projectionMat);
    
    return projectionPos;
}