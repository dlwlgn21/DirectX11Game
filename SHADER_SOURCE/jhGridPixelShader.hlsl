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
    float4 Out = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    const int WIDTH = 100;
    const int HEIGHT = 100;
    
    uint worldX = (int) _in.WorldPos.x;
    uint worldY = (int) _in.WorldPos.y;
    
    const float THICKNESS = 1.0f;
    
    if (abs(worldX + 1) % WIDTH <= THICKNESS)
    {
        discard;
        return Out;
    }
    
    if (abs(worldY + 1) % HEIGHT <= THICKNESS)
    {
        discard;
        return Out;
    }
    
    discard;
    
    return float4(1.0f, 0.1f, 1.0f, 0.0f);
}