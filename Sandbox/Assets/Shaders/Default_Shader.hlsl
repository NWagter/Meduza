float4 VS(float3 pos : POSITION) : SV_POSITION
{
    return float4(pos, 1.0f);
}

float4 PS() : SV_TARGET
{
    return float4(0.0f, 1.0f, 0.0f, 1.0f); // Red, Green, Blue, Alpha
}