//Buffer data from big to small.

cbuffer cbPerObject : register(b0)
{
	float4x4 viewProjection;
	float3 position = float3(0, 0, 0);
	float3 scale = float3(1, 1, 1);
};


struct VS_INPUT
{
	float3 pos : POSITION;
	float4 colour : COLOR;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 colour : COLOR;
};

VS_OUTPUT VS(VS_INPUT a_input)
{
	VS_OUTPUT outPut;

	float3 newPos = a_input.pos * scale;

	newPos = newPos + position;

	float4 pos = mul(float4(newPos, 1.f), viewProjection);
	outPut.colour = a_input.colour;
	outPut.pos = pos;

	return outPut;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
	return a_input.colour;
}