#ifndef RENDERER_DEFINE_H
#define RENDERER_DEFINE_H

namespace KI
{
namespace ShaderLib
{
#define SHADER_DIRECTORY	"E:\\MyProgram\\KIProject\\CGALRenderer\\Resource\\"
#define SHADER_EXT_VERTEX	".vert"
#define SHADER_EXT_TES		".tes"
#define SHADER_EXT_TCS		".tcs"
#define SHADER_EXT_GEOM		".geom"
#define SHADER_EXT_FRAG		".frag"
#define SHADER_EXT_VBO		".vbo"
#define SHADER_EXT_TXT		".txt"


#define SHADER_DEFAULT		"default"
#define SHADER_COMMON		"common/common"
#define SHADER_POSTPROCESS	"postprocess"
#define SHADER_GRAYSCALE	"grayscale"
#define SHADER_COMPOSIT		"composit"
#define SHADER_SSLIC		"sslic"
#define SHADER_NORMALVIS	"normalvisualize"
#define SHADER_BEZIERLINE	"bezierline"
#define SHADER_OUTPUT		"output"
#define SHADER_PICK			"pick"
#define SHADER_STRUCT		"common/struct.h"
#define SHADER_BASICSHADING "material/basicmaterial"
#define SHADER_PHONGSHADING "material/phongmaterial"
#define SHADER_LAMBERTSHADING "material/lambertmaterial"
#define SHADER_VERTEXSHADING "material/vertexmaterial"


#define GLSL_VERSION_400_CORE "#version 400 core\n"
#define IN_NORMAL		"#define IN_NORMAL\n"
#define IN_COLOR		"#define IN_COLOR\n"
#define IN_TEXCOORD		"#define IN_TEXCOORD\n"
#define IN_TEXTURE0		"#define IN_TEXTURE0\n"
#define IN_INSTANCE		"#define IN_INSTANCE\n"
#define VIEW_NORMAL		"#define VIEW_NORMAL\n"


#define USE_GBUFFER		"#define USE_GBUFFER\n"
#define USE_SHADING		"#define USE_SHADING\n"

#define SCENE_DATA_LOCATION		5
#define LIGHT_DATA_LOCATION		6
#define MODEL_DATA_LOCATION		7
#define MATERIAL_DATA_LOCATION	8
}
}
#endif RENDERER_DEFINE_H