#include "./ShaderTypeDefs.hlsl"

WAVE_DEBUGGING_PS_IN main(WAVE_DEBUGGING_VS_IN input)
{
    WAVE_DEBUGGING_PS_IN output;
    
    input.iPosL.w = 1.0;

    output.iPos = input.iPosL;

    output.iNorm = input.iNormL;

    output.iVertColor = input.iVertColor;

    return output;
}