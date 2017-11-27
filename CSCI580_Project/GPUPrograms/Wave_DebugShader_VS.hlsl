#include "./ShaderTypeDefs.hlsl"

WAVE_DEBUGGING_PS_IN main(WAVE_DEBUGGING_VS_IN input)
{
    WAVE_DEBUGGING_PS_IN output;

    output.iPos = float4(input.iPosL, 1.0);

    output.iNorm = input.iNormL;

    return output;
}