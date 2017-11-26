#include "./ShaderTypeDefs.hlsl"

/****
* float4 main(DEBUGGING_PS_IN input) : SV_TARGET
*
* Output float4 - Represents the color that will be painted to a pixel
* 
* Input DEBUGGING_PS_IN input - The struct that is taken as input by this shader
*
* SV_TARGET - Paint to the current render target (you can actually dictate multiple SV_TARGET1 etc...)
*/
float4 main( WAVE_DEBUGGING_PS_IN input ) : SV_TARGET
{
    // TODO add lighting calculations
    
    return input.iVertColor;
}