#include "globals.hlsli"


float4 main(VSOut _in) : SV_Target
{
    float4 color = (float) 0.0f;
    
    //if (Xy.x == 1.0f)
    //{
    //    return float4(1.0f, 1.0f, 0.0f, 1.0f);
    //}
    
    color = defaultTexture.Sample(anisotropicSampler, _in.UV);
    return color;
}