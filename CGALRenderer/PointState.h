#ifndef POINT_MATERIAL_H

namespace KI
{

class PointState : public IRasterState
{
public:
	PointState();
	~PointState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_POINT; }
	void SetPointSize(GLuint value) { m_pointSize = value; }
	GLuint GetPointSize() { return m_pointSize; }
	GLuint const GetPointSize() const { return m_pointSize; }

	virtual void Bind() override;
	virtual void UnBind() override;

	virtual bool Compare(const IGLState& state) override;

private:
	GLuint m_pointSize;
};

}


#define POINT_MATERIAL_H
#endif POINT_MATERIAL_H