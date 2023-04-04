#include "globals.hlsli"

struct ParticleVSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID;         // 몇 번째 물체인지가 자동으로 이 변수로 들어옴
};

struct ParticleVSOut
{
    float4 Pos : SV_POSITION;
    uint iInstance : SV_InstanceID;         // 몇 번째 물체인지가 자동으로 이 변수로 들어옴
};

ParticleVSOut main(ParticleVSIn _pVin)
{
    ParticleVSOut Out = (ParticleVSOut) 0.0f;
    Out.Pos = _pVin.Pos;
    Out.iInstance = _pVin.iInstance;

    return Out;
}