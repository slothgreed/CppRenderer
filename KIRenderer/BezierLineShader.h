#ifndef BEZIER_LINE_SHADERL_H
#define BEZIER_LINE_SHADERL_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT BezierLineShader : public IShader
{
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

	enum BEZIERLINE_UNIFORM : unsigned short
	{
		BEZIERLINE_UNIFORM_SEGMENT_NUM,
		BEZIERLINE_UNIFORM_STRIP_NUM,
		BEZIERLINE_UNIFORM_NUM
	};

public:
	BezierLineShader();
	~BezierLineShader();
	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<UniformSet> pUniform) override;
	void SetPatchVertices(GLuint patchVertex);
private:
	void BindScene();
	GLuint m_patchVertex;
};

class DLL_EXPORT BezierLineUniform : public IUniform
{
public:
	BezierLineUniform() : m_SegmentNum(10),m_StripNum(1) {}
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }

	void SetSegmentNum(int value) { m_SegmentNum = value; };
	void SetStripNum(int value) { m_StripNum = value; };

	int SegmentNum() { return m_SegmentNum; }
	int StripNum() { return m_StripNum; }
private:
	int m_SegmentNum;
	int m_StripNum;
	
};
}
}


#endif BEZIER_LINE_SHADERL_H
