#include "./ShaderTypeDefs.hlsl"

DEBUGGING_PS_IN main(DEBUGGING_VS_IN input)
{
	DEBUGGING_PS_IN output;

	output.position = input.iPosL;

	return output;
}