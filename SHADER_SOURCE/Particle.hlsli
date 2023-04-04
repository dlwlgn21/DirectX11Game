struct Particle
{
    float4 Position;
    float4 Direction;
    
    float LifeTime;
    float CurrTime;
    float Speed;
    uint  IsActive;
};