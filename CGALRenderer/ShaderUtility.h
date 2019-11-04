#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H

enum VERTEX_LAYOUT;
class ShaderUtility
{
public:
	ShaderUtility();
	~ShaderUtility();
	
	static void GetVertexShaderDefine(VERTEX_LAYOUT layout, std::string& vertexFilePath);
private:

};

#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"


#endif SHADER_UTILITY_H
