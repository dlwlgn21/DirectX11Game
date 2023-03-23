
RWTexture2D<float4> tex : register(u0);
// RW 뜻 : Read, Write 가능
// SV_GroupID: : 쓰레드에 속한 그룹의 좌표 (Z값)
// SV_GroupThreadID: : 그룹 내에서 쓰레드의 좌표(X, Y값)
// SV_GroupIndex : 그룹 내에서 쓰레드의 인덱스 좌표(1차원)
// SV_DispatchThreadID : 전체 쓰레드 기준으로 호출된 좌표

[numthreads(32, 32, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    const uint MAX_THREAD_COUNT = 1024;
    if (DTid.x >= MAX_THREAD_COUNT || DTid.y >= MAX_THREAD_COUNT)
    {
        return;
    }
    tex[DTid.xy] = float4(1.0f, 0.0f, 1.0f, 1.0f);

}