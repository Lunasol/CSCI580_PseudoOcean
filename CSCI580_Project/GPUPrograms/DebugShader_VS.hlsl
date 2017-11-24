#include "./ShaderTypeDefs.hlsl"

DEBUGGING_PS_IN main(DEBUGGING_VS_IN input)
{
	DEBUGGING_PS_IN output;

	input.iPosL.w = 1.0f;

	output.position = input.iPosL;

	output.color = input.iVertColor;

	return output;
}