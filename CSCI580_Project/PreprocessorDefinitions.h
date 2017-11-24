/**
* PreprocessorDefinitions.h
*
* This is the adaption of the d3d11 tutorial file.  This struct is representative of
* the D3D11 Render Target.  All shaders must be compiled here and all geometry must be
* sent here as well.
*/
#ifndef __PREPROCESSOR_DEFINITIONS_H__
#define __PREPROCESSOR_DEFINITIONS_H__

// Screen Definitions
#define SCREENWIDTH 640
#define SCREENHEIGHT 480

// Shader Type Definitions
#define VSPROFILE "vs_5_0"
#define GSPROFILE "gs_5_0"
#define PSPROFILE "ps_5_0"
#define CSPROFILE "cs_5_0"

// Simplistic Functions As Macros
#define EALLOC(type, amount) ( type *) malloc(sizeof( type ) * amount )

#endif