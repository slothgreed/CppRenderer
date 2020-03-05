#ifndef LINE_MATERIAL_H
#define LINE_MATERIAL_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT LineState : public IRasterState
{
public:
	LineState();
	~LineState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_LINE; }

	void SetLineWidth(GLfloat value) { m_lineWidth = value; }
	GLfloat GetLineWidth() { return m_lineWidth; }
	GLfloat const GetLineWidth() const { return m_lineWidth; }

	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	GLfloat m_lineWidth;
};

}
}
#endif LINE_MATERIAL_H
