cbuffer cbPerObject : register(b0)
{
	float4x4 transform;
	float4 colour;
}

struct VS_INPUT {
	float3 pos : POSITION;
};

struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float4 colour: COLOUR;
};

VS_OUTPUT main(VS_INPUT a_input)
{
	VS_OUTPUT outPut;
	float4 newPos = mul(float4(a_input.pos, 1.f), transform);
	outPut.pos = newPos;
	outPut.colour = colour;

	return outPut;
}