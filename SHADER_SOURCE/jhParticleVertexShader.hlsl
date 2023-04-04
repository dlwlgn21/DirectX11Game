#include "globals.hlsli"

struct ParticleVSIn
{
    float4 Pos : POSITION;
    uint iInstance : SV_InstanceID;         // �� ��° ��ü������ �ڵ����� �� ������ ����
};

struct ParticleVSOut
{
    float4 Pos : SV_POSITION;
    uint iInstance : SV_InstanceID;         // �� ��° ��ü������ �ڵ����� �� ������ ����
};

ParticleVSOut main(ParticleVSIn _pVin)
{
    ParticleVSOut Out = (ParticleVSOut) 0.0f;
    Out.Pos = _pVin.Pos;
    Out.iInstance = _pVin.iInstance;

    return Out;
}