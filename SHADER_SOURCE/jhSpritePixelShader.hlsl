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
    float3 WolrdPos : POSITION; // PS에서 라이팅 계산하기 위해 보내주는 정보.
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut _in) : SV_Target
{
    float4 color = (float) 0.0f;
    const uint SECOND_DIMENTION = 1;
    const uint THIRD_DIMENTION = 2;
    
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
    }
    else
    {
        //color = defaultTexture.Sample(pointSampler, _in.UV);
        color = defaultTexture.Sample(pointSampler, _in.UV);
    }

    //LightColor lightColor = (LightColor)0.0f;
    //for (uint i = 0; i < NumberOfLight; ++i)
    //{
    //    CalculateLight(lightColor, _in.WolrdPos, i);
    //}
    
    //if (NumberOfLight <= 0)
    //{
    //    lightColor = (LightColor)1.0f;
    //}
    
    //color *= lightColor.Diffuse;
    
    //return float4(cos(fData * 7), sin(fData * 3), cos(fData * 2), 1.0f);
    return color;
}