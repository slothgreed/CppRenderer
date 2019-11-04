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

#endif SHADER_UTILITY_H
