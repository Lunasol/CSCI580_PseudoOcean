#ifndef __SHADER_TYPE_DEFS_HLSL__
#define __SHADER_TYPE_DEFS_HLSL__

// For more about the Semantic names please read 
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx

// Debugging Structs
struct DEBUGGING_VS_IN
{
	float4 iPosL : POSITION;
	float4 iVertColor : COLOR;
};

struct DEBUGGING_PS_IN
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

// Wave Debugging
struct WAVE_DEBUGGING_VS_IN
{
	float4 iPosL : POSITION;
	float3 iNormL : NORMAL;
	float4 iVertColor : COLOR;
}

struct WAVE_DEBUGGING_PS_IN
{
	float4 iPos : SV_Position;
	float4 iNorm : NORMAL;
	float4 iVertColor : COLOR;
}
// End Debugging 

#endif