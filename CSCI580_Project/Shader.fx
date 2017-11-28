/*

% Does Per pixel Phong Shading Calculation.
% Input Vertex Position, Normal and Texture if any or color information


keywords: Phong Shading for realistic water simulation

date: 11/26/2017

*/

float4x4 WorldViewProj : WorldViewProjection;
float4x4 World : World;

//Texture Variables//
Texture2D colorMap;

SamplerState linearSampler
{
	Filter = min_mag_mip_linear;
    AddressU = Clamp;
    AddressV = Clamp;
    MaxAnisotropy = 16;
};

//Rasterizer State
RasterizerState raster
{
	FillMode = solid; 
	// FillMode : Solid / Wireframe
	CullMode = NONE;
	FrontCounterClockwise = false;
};

//Light Structure and Variables//

struct DirectionalLight
{
	float4 color;
	float3 dir;
};

struct Material
{
	float Ka,Kd,Ks,specPow;	
};






float3 eye;



// Vertex and Pixel Shader structures

struct VS_INPUT
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal: NORMAL;
};

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 worldPosition: POSITION1;
	float2 tex: TEXCOORD;
	float3 normal: TEXCOORD1;	
};



// Phong Color Calculation
// M: Material Coefficients
// LColor: Light Color
// N: Normal vector
// L: Light Vector
// V: Eye Vector
// R: Reflected Vector

float4 calcPhong(Material M, float4 LColor, float3 N,float3 L, float3 V,float3 R)
{
	float4 ambientLight ;
	ambientLight = float4(0.7f,0.0f,0.0f,1.0f);
	float4 Ia= M.Ka * ambientLight;
	float4 Id = M.Kd * saturate(dot(N,L));
	float4 Is = M.Ks * pow(saturate(dot(R,V)),M.specPow);
	
	//return float4(Is);
	return float4(Ia+((Id+Is)*LColor));
}

PS_INPUT mainVS(VS_INPUT input)
{
	PS_INPUT output;
	// Transform the position to the projection space
	output.position = mul(input.position,WorldViewProj);
	output.worldPosition = mul(input.position,World);
	
	// Texture Coord
	output.tex = input.tex;

	output.normal = normalize(mul(input.normal,(float3x3)World));
	
	return output;
}

float4 mainPS(PS_INPUT input) : SV_Target
{
	DirectionalLight light;
	light.dir = normalize(float3(1,-1,0));
	light.color = normalize(float4(1.0f,1.0f,1.0f,1.0f));
	
	Material material;
	material.Ka = 0.5f;
	material.Kd = 0.5f;
	material.Ks = 0.5f;
	material.specPow = 30;
	
	
	
	input.normal = normalize(input.normal);
	
	float3 V = normalize (eye - (float3)input.worldPosition);
	
	float3 R = reflect(light.dir,input.normal);
	
	float4 I = calcPhong(material,light.color,input.normal,-light.dir,V,R);
	
	// Incase return with texture.
	//return I*colorMap.Sample(linearSampler,input.tex);
	
	
	
	return I;

	
}

// Techniques

technique10 RENDER 
{
	pass p0 
	{
		SetVertexShader( CompileShader( vs_4_0, mainVS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, mainPS() ) );
        SetRasterizerState( raster );
	}

}
