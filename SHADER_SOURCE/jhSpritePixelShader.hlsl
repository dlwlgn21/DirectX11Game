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

const uint SECOND_DIMENTION = 1;
const uint THIRD_DIMENTION = 2;

float4 main(VSOut _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    if (animationType == SECOND_DIMENTION)
    {
        float2 diff = (atlasImageSize - spriteSize) * 0.5f;
        float2 uv = (leftTop - diff - offset) + (atlasImageSize * _in.UV);
        if (uv.x < leftTop.x ||
            uv.y < leftTop.y ||
            uv.x > leftTop.x + spriteSize.x ||
            uv.y > leftTop.y + spriteSize.y)
        {
            discard;
        }
        color = atlasTexture.Sample(pointSampler, uv);
        return color;
    }
    else
    {
        //color = defaultTexture.Sample(pointSampler, _in.UV);
    }
    color = defaultTexture.Sample(pointSampler, _in.UV);

    return color;
}