


struct VertexIn
{
    float3 pos : POSITION;
    float4 color : COLOR;
    //float3 normal : NORMAL;
    //float2 texcoord : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    vout.PosH = float4(vin.pos, 1.0f);
    vout.Color = vin.color;
    
    return vout;
}

float4 PS(VertexOut pin) : SV_TARGET
{
    return pin.Color;
}