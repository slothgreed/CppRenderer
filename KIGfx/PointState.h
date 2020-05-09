#ifndef POINT_STATE_H
#define POINT_STATE_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT PointState : public IRasterState
{
public:

	PointState(GLfloat pointSize, GLboolean depthTest = false);
	~PointState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_POINT; }
	void SetPointSize(GLfloat value) { m_pointSize = value; }
	GLfloat GetPointSize() { return m_pointSize; }
	GLfloat const GetPointSize() const { return m_pointSize; }

	virtual void Bind() override;
	virtual void UnBind() override;

	virtual bool Compare(const IGLState& state) override;

private:
	GLfloat m_pointSize;
	GLboolean m_depthTest;
};
}
}

#endif POINT_STATE_H