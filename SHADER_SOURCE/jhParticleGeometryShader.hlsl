#include "globals.hlsli"

struct ParticleVSOut
{
    float4 Pos : SV_POSITION;
    uint iInstance : SV_InstanceID; // 몇 번째 물체인지가 자동으로 이 변수로 들어옴
};
struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

    [maxvertexcount(6)]
void main(
	point ParticleVSOut input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output     // 이걸로 픽셀셰이더로 보냄
)
{
    GSOutput Out[4] = { (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f, (GSOutput) 0.0f };
    if (0 == particleBuffer[input[0].iInstance].IsActive)
    {
        return;
    }
    
    float3 vWorldPos = input[0].Pos.xyz + particleBuffer[input[0].iInstance].Position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), viewMat);
    
    
    float3 NewPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, 0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f),
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * float3(50.0f, 50.0f, 1.0f)
    };
    
    
    for (int i = 0; i < 4; ++i)
    {
        Out[i].Pos = mul(float4(NewPos[i], 1.0f), projectionMat);

    }
    
    Out[0].UV = float2(0.0f, 0.0f);
    Out[1].UV = float2(1.0f, 0.0f);
    Out[2].UV = float2(1.0f, 1.0f);
    Out[3].UV = float2(0.0f, 1.0f);

    // 메시가 아래와 같이 만들어진 것
    // 0 -- 1
    // |    |
    // 3 -- 2
    
    output.Append(Out[0]);
    output.Append(Out[1]);
    output.Append(Out[2]);
    output.RestartStrip();
    
    output.Append(Out[0]);
    output.Append(Out[2]);
    output.Append(Out[3]);
    output.RestartStrip();
}