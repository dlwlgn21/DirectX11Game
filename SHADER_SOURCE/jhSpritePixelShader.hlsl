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
const uint SECOND_DIMENTION = 0;
const uint THIRD_DIMENTION = 1;

float4 main(VSOut _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    if (animationType == SECOND_DIMENTION)
    {
        float2 diff = (atlasImageSize - spriteSize) * 0.5f;
        float2 uv = (leftTop - offset) + (atlasImageSize * _in.UV);
        color = atlasTexture.Sample(pointSampler, uv);

    }
    else if (animationType == THIRD_DIMENTION)
    {
        
    }
    else
    {
       // NO ANIM
       color = defaultTexture.Sample(pointSampler, _in.UV);
    }
    return color;
}