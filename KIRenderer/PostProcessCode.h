#ifndef POSTPROCESS_VERTEX_CODE_H
#define POSTPROCESS_VERTEX_CODE_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT PostProcessVertexCode : public IShaderCode
{
public:
	PostProcessVertexCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_POSTPROCESS) +
			string(SHADER_EXT_VERTEX)) {};
	~PostProcessVertexCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_POSTPROCESS; }

private:

};

class DLL_EXPORT GrayScaleFragCode : public IShaderCode
{
public:
	GrayScaleFragCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_GRAYSCALE) +
			string(SHADER_EXT_FRAG)) {};
	~GrayScaleFragCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_GRAYSCALE; }
};

class DLL_EXPORT OutputFragCode : public IShaderCode
{
public:
	OutputFragCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_OUTPUT) +
			string(SHADER_EXT_FRAG)) {};
	~OutputFragCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }

};

class DLL_EXPORT SSLICFragCode : public IShaderCode
{
public:
	SSLICFragCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_SSLIC) +
			string(SHADER_EXT_FRAG)) {};
	~SSLICFragCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_SSLIC; }

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

}
}

#endif POSTPROCESS_VERTEX_CODE_H