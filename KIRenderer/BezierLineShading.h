#ifndef BEZIER_LINE_SHADING_H
#define BEZIER_LINE_SHADING_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT BezierLineTCSCode : public IShaderCode
{
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

	enum BEZIERLINE_UNIFORM : unsigned short
	{
		BEZIERLINE_UNIFORM_SEGMENT_NUM,
		BEZIERLINE_UNIFORM_STRIP_NUM,
		BEZIERLINE_UNIFORM_NUM
	};

public:
	BezierLineTCSCode();
	~BezierLineTCSCode();
	virtual void Initialize(GLuint programId) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
private:
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
	virtual void Initialize(GLuint programId) override {};
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
};

class DLL_EXPORT BezierLineShading : public IShading
{
public:
	BezierLineShading() : m_SegmentNum(10),m_StripNum(1), m_patchVertex(0) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

	void SetSegmentNum(int value) { m_SegmentNum = value; };
	void SetStripNum(int value) { m_StripNum = value; };

	int SegmentNum() { return m_SegmentNum; }
	int StripNum() { return m_StripNum; }
	void SetPatchVertices(GLuint patchVertex);
	GLuint GetPatchVertices() { return m_patchVertex; };

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type);

private:
	int m_SegmentNum;
	int m_StripNum;
	GLuint m_patchVertex;

};
}
}

#endif BEZIER_LINE_SHADING_H
