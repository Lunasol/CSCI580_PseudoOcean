#include "./ShaderTypeDefs.hlsl"

WAVEMESH_PS_IN main(WAVEMESH_VS_IN input)
{
    WAVE_DEBUGGING_PS_IN output;
    
    
    output.iPos.w = 1.0;

    output.iPos = input.iPosL;

    output.iNorm = input.iNormL;

    output.iVertColor = input.iVertColor;

    return output;
}