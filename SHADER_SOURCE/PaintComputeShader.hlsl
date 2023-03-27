#include "globals.hlsli"


RWTexture2D<float4> tex : register(u0);
// RW �� : Read, Write ����
// SV_GroupID: : �����忡 ���� �׷��� ��ǥ (Z��)
// SV_GroupThreadID: : �׷� ������ �������� ��ǥ(X, Y��)
// SV_GroupIndex : �׷� ������ �������� �ε��� ��ǥ(1����)
// SV_DispatchThreadID : ��ü ������ �������� ȣ��� ��ǥ

[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    const uint MAX_THREAD_COUNT = 1024;
    if (DTid.x >= MAX_THREAD_COUNT || DTid.y >= MAX_THREAD_COUNT)
    {
        return;
    }
    tex[DTid.xy] = float4(cos(fData * 2), sin(fData * 3), tan(fData * 17), 1.0f);

    //tex[DTid.xy] = float4(a, 1.0f, c, 1.0f);
    
    

}