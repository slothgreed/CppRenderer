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

class DLL_EXPORT BezierLineTCSCode : public IShaderCode
{
public:
	BezierLineTCSCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_BEZIERLINE) +
			string(SHADER_EXT_TCS)) {};
	~BezierLineTCSCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

};

class DLL_EXPORT BezierLineTESCode : public IShaderCode
{
public:
	BezierLineTESCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_BEZIERLINE) +
			string(SHADER_EXT_TES)) {};
	~BezierLineTESCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

};

class DLL_EXPORT PickFragCode : public IShaderCode
{
public:
	PickFragCode()
		: IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_PICK) +
			string(SHADER_EXT_FRAG)) {};
	~PickFragCode() {};

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }
};

#endif SIMPLE_SHADER_CODE_H