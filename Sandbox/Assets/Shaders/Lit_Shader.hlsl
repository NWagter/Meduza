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
    float3 normal : NORMAL;
    float2 texC: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 posH : SV_POSITION;
    float4 colour : COLOUR;
	float3 posW : POSITION;
    float3 normal : NORMAL;
    float2 texC: TEXCOORD;
    nointerpolation int textureId : TEXTID;
};

VS_OUTPUT VS(VS_INPUT input, uint instanceID : SV_InstanceID)
{
    VS_OUTPUT output;
    
	InstanceData data = gInstanceData[instanceID];

    float4 pos = mul(float4(input.pos, 1.f), data.model);  
    output.posW = pos.xyz;
    output.posH = mul(pos, viewProjection);

    output.colour = data.colour;

	float4 tCoord = data.textureCoord;
    output.texC = float2(tCoord.x + (tCoord.z * input.texC.x),
			            tCoord.y + (tCoord.w * input.texC.y));

    output.textureId = data.textureId;

    output.normal = mul(input.normal, (float3x3)data.model);

    return output;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
    float4 c = gDiffuseMap[a_input.textureId].Sample(gsamLinear, a_input.texC) * a_input.colour;

    float3 ambient = float3(0.4f, 0.4f, 0.4f) * c.xyz;
    float3 N = normalize(a_input.normal);

    float3 light = float3(1,0,-1);
    float3 lightDir = normalize(light);   

    float diff = max(dot(N, lightDir), 0.0f);
    float3 diffuse = float3(0.8f, 0.8f, 0.8f) * diff * (c.xyz);

    float4 result = float4(ambient + diffuse, c.w);
    return result;
}