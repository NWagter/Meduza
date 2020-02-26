cbuffer cbPerObject : register(b0)
{
	float4 position : POSITION;
}

float4 main(float3 pos : POSITION) : SV_POSITION
{
	float4 newPos = float4(pos, 1);
	newPos.x += position.x;
	newPos.y += position.y;

	return newPos;
}