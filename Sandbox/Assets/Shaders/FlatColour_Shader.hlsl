Texture2D gDiffuseMap[1] : register(t0);
SamplerState gsamLinear  : register(s0);

struct InstanceData
{
	float4x4 model;
	float4 colour;
    float4 textureCoord;
	int textureId;
};
StructuredBuffer<InstanceData> gInstanceData : register(t1, space1);

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
	float4 posH : SV_POSITION;
    float4 colour : COLOUR;
	float3 posW : POSITION;
    float2 texC: TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input, uint instanceID : SV_InstanceID)
{
    VS_OUTPUT output;
    
	InstanceData data = gInstanceData[instanceID];

    float4 pos = mul(float4(input.pos, 1.f), data.model);  
    output.posW = pos.xyz;
    output.posH = mul(pos, viewProjection);

    output.colour = data.colour;
    output.texC = input.texC;
    return output;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
    return a_input.colour;
}