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

float4 main(VSOut _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    //if (Xy.x == 1.0f)
    //{
    //    return float4(1.0f, 1.0f, 0.0f, 1.0f);
    //}
    
    color = defaultTexture.Sample(pointSampler, _in.UV);
    return color;
}