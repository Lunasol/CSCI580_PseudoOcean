///////////////////////////////////////////////////////
// Global Constants
///////////////////////////////////////////////////////

/////////////////////////////////
// Lights struct
/////////////////////////////////
struct PointLight {
    float4 iPositionW;
    float4 iDirW;
    float4 iLightColor;
    float iKD; 
    float iKS;
    float iSpecPower;
}

cbuffer VS_CONSTANT_BUFFER : register(b0)
{
    float4x4 mWorldViewProj; // World view projection mat
    float fTime; // time
}

cbuffer PS_CONSTANT_BUFFER : register(b1)
{
    PointLight cSunLight; // light
}