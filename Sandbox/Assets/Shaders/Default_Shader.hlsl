Texture2D gDiffuseMap[1] : register(t0);
SamplerState gsamLinear  : register(s0);

cbuffer CameraBuffer : register(b0)
{
    float4x4 viewProjection;
};

struct VS_INPUT
{
    float3 pos : POSITION;
    float2 texC: TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos: SV_POSITION;
    float2 texC: TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    float4 pos = float4(input.pos, 1);    
    output.pos = mul(pos, viewProjection);

    output.texC = input.texC;
    return output;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
    return gDiffuseMap[0].Sample(gsamLinear, a_input.texC);
}