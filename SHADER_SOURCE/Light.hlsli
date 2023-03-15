struct LightColor
{
    float4 Diffuse;
    float4 Specular;
    float4 Ambient;
};

struct LightAttribute
{
    LightColor Color;
    float4 Position;
    float4 Direction;
    
    int Type;
    float Radius;
    float Angle;
    int Padding;
}; 