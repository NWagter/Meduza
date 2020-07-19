//Buffer data from big to small.


/*cbuffer cbPerObject : register(b0)
{
	float4x4 viewProjection;
};*/


struct VS_INPUT
{
	float3 pos : POSITION;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 colour : COLOR;
};

VS_OUTPUT VS(VS_INPUT a_input)
{
	VS_OUTPUT outPut;

	float4 pos = float4(a_input.pos, 1.f);
	outPut.colour = float4(1, 1, 1, 1);
	outPut.pos = pos;

	return outPut;
}

float4 PS(VS_OUTPUT a_input) : SV_TARGET
{
	return a_input.colour;
}