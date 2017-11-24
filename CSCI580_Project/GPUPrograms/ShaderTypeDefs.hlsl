#ifndef __SHADER_TYPE_DEFS_HLSL__
#define __SHADER_TYPE_DEFS_HLSL__

// Debugging Structs
struct DEBUGGING_VS_IN
{
	float4 iPosL : POSITION;
	float4 iVertColor : COLOR;
};

struct DEBUGGING_PS_IN
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};
// End Debugging 

#endif