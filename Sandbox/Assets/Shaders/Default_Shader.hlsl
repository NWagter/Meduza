Texture2D gDiffuseMap[1] : register(t0);
SamplerState gsamLinear  : register(s0);

struct InstanceData
{
	float4 colour;
    float3 position;
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
    float4 pos: SV_POSITION;
    float4 colour : COLOUR;
    float2 texC: TEXCOORD;
    nointerpolation int textureId : TEXTID;
};

VS_OUTPUT VS(VS_INPUT input, uint instanceID : SV_InstanceID)
{
    VS_OUTPUT output;
    
	InstanceData data = gInstanceData[instanceID];

    float3 newPos = (input.pos * 32 ) + data.position;
    float4 pos = float4(newPos, 1);    
    output.pos = mul(pos, viewProjection);

    output.colour = data.colour;
    output.texC = input.texC;
    output.textureId = data.textureId;
    return output;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
    return gDiffuseMap[a_input.textureId].Sample(gsamLinear, a_input.texC);
}