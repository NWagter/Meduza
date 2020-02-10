float4 main(float3 pos : POSITION) : SV_POSITION
{
	float3 newPos = {pos.x + 0.5f, pos.y,pos.z};
	return float4(newPos, 1.0f);
}