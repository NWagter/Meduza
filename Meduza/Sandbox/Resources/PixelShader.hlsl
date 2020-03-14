struct VS_OUTPUT
{
	float4 pos: SV_POSITION;
	float4 colour: COLOUR;
};

float4 main(VS_OUTPUT a_input) : SV_TARGET
{
	return a_input.colour;
}