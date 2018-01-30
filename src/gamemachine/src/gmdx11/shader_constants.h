﻿#ifndef __GMDX11_SHADER_CONSTANTS_H__
#define __GMDX11_SHADER_CONSTANTS_H__
#include <gmcommon.h>
#include <gmdxincludes.h>
BEGIN_NS

// 与GMModel里面定义的顶点结构要保持一致
#define GMSHADER_LAYOUT_NAME_POSITION "POSITION"
#define GMSHADER_LAYOUT_NAME_NORMAL "NORMAL"
#define GMSHADER_LAYOUT_NAME_UV "TEXCOORD"
#define GMSHADER_LAYOUT_NAME_TANGENT "TANGENT"
#define GMSHADER_LAYOUT_NAME_BITANGENT "BITANGENT"
#define GMSHADER_LAYOUT_NAME_LIGHTMAP "LIGHTMAP"
#define GMSHADER_LAYOUT_NAME_COLOR "COLOR"

D3D11_INPUT_ELEMENT_DESC GMSHADER_ElementDescriptions[] = 
{
	{ GMSHADER_LAYOUT_NAME_POSITION, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ GMSHADER_LAYOUT_NAME_COLOR, 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

END_NS
#endif