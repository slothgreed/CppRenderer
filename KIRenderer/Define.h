#ifndef RENDERER_DEFINE_H
#define RENDERER_DEFINE_H

namespace KI
{
namespace Rednerer
{
#define SHADER_DIRECTORY	"E:\\MyProgram\\KIProject\\CGALRenderer\\Resource\\"
#define SHADER_EXT_VERTEX	".vert"
#define SHADER_EXT_FRAG		".frag"
#define SHADER_EXT_GEOM		".geom"


#define SHADER_DEFAULT		"default"
#define SHADER_POSTPROCESS	"postprocess"
#define SHADER_GRAYSCALE	"grayscale"
#define SHADER_COMPOSIT		"composit"
#define SHADER_SSLIC		"sslic"
#define SHADER_OUTPUT		"output"


#define GLSL_VERSION_400_CORE "#version 400 core\n"
#define USE_NORMAL	 "#define USE_NORMAL\n"
#define USE_COLOR	 "#define USE_COLOR\n"
#define USE_TEXCOORD "#define USE_TEXCOORD\n"
#define USE_TEXTURE0 "#define USE_TEXTURE0\n"
#define USE_GBUFFER	 "#define USE_GBUFFER\n"
#define USE_SHADING	 "#define USE_SHADING\n"
#define USE_INSTANCE "#define USE_INSTANCE\n"

#define SCENE_DATA_LOCATION		5
#define LIGHT_DATA_LOCATION		6
#define MODEL_DATA_LOCATION		7
#define MATERIAL_DATA_LOCATION	8
}
}
#endif RENDERER_DEFINE_H