//Buffer data from big to small.

cbuffer cbPerObject : register(b0)
{
	float4x4 viewProjection;
};

struct VS_INPUT
{
	float3 vertPos : POSITION0;
	float3 position : POSITION1;
	float3 scale : PSIZE;
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

	float3 newPos = a_input.vertPos * a_input.scale;

	newPos = newPos + a_input.position;

	float4 pos = mul(float4(newPos, 1.f), viewProjection);
	outPut.colour = a_input.colour;
	outPut.pos = pos;

	return outPut;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
	return a_input.colour;
}