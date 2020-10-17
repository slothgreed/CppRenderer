#ifndef GL_TYPES_H
#define GL_TYPES_H

namespace KI
{
namespace Gfx
{

enum SHADER_PROGRAM_TYPE
{
	SHADER_PROGRAM_VERTEX	= 0,
	SHADER_PROGRAM_FRAG		= 1,
	SHADER_PROGRAM_TCS		= 2,
	SHADER_PROGRAM_TESS		= 3,
	SHADER_PROGRAM_GEOM		= 4,
	SHADER_PROGRAM_NUM		= 5,
};

// depth or stencil
enum COMP_FUNC
{
	COMP_FUNC_NEVER = 0x0200,
	COMP_FUNC_LESS = 0x0201,
	COMP_FUNC_EQUAl = 0x0202,
	COMP_FUNC_LEQUAL = 0x0203,
	COMP_FUNC_GREATER = 0x0204,
	COMP_FUNC_NOTEQUAL = 0x0205,
	COMP_FUNC_GEQUAL = 0x0206,
	COMP_FUNC_ALWAYS = 0x0207
};

enum FRONT_FACE
{
	FRONT_FACE_CW	= 0x0900,
	FRONT_FACE_CCW	= 0x0901
};

enum CULL_MODE
{
	CULL_MODE_FRONT				= 0x0404,
	CULL_MODE_BACK				= 0x0405,
	CULL_MODE_FRONT_AND_BACK	= 0x0408
};

enum BLEND_FACTOR
{
	BLEND_FACTOR_ZERO = 0,
	BLEND_FACTOR_ONE = 1,
	BLEND_FACTOR_SRC_COLOR				= 0x0300,
	BLEND_FACTOR_ONE_MINUS_SRC_COLOR	= 0x0301,
	BLEND_FACTOR_SRC_ALPHA				= 0x0302,
	BLEND_FACTOR_ONE_MINUS_SRC_ALPHA	= 0x0303,
	BLEND_FACTOR_DST_ALPHA				= 0x0304,
	BLEND_FACTOR_ONE_MINUS_DST_ALPHA	= 0x0305,
	BLEND_FACTOR_DST_COLOR				= 0x0306,
	BLEND_FACTOR_ONE_MINUS_DST_COLOR	= 0x0307,
	BLEND_FACTOR_ONE_MINUS_SRC1_COLOR	= 0x88FA,
	BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA	= 0x88FB,
};

enum PRIM_TYPE
{
	PRIM_TYPE_NONE				= 0xFFFF,
	PRIM_TYPE_POINTS			= 0x0000,
	PRIM_TYPE_LINES				= 0x0001,
	PRIM_TYPE_LINE_STRIP		= 0x0002,
	PRIM_TYPE_LINE_LOOP			= 0x0003,
	PRIM_TYPE_TRIANGLES			= 0x0004,
	PRIM_TYPE_TRIANGLE_STRIP	= 0x0005,
	PRIM_TYPE_TRIANGLE_FAN		= 0x0006,
	PRIM_TYPE_PATCHES			= 0xE
};


}
}

#endif GL_TYPES_H