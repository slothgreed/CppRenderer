#ifndef SIMPLE_SHADER_CODE_H
#define SIMPLE_SHADER_CODE_H

class DLL_EXPORT NormalVisualizeGeometryCode : public IShaderCode
{
public:
	NormalVisualizeGeometryCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_NORMALVIS) +
			string(SHADER_EXT_GEOM)) {};
	~NormalVisualizeGeometryCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE; }

};

#endif SIMPLE_SHADER_CODE_H