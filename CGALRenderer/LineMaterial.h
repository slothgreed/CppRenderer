#ifndef LINE_MATERIAL_H
#define LINE_MATERIAL_H

namespace KI
{

class LineMaterial : public DefaultMaterial
{
public:
	LineMaterial();
	~LineMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE_LINEMATERIAL; }

	void SetLineWidth(GLfloat value) { m_lineWidth = value; }
	GLfloat GetLineWidth() { return m_lineWidth; }
	GLfloat const GetLineWidth() const { return m_lineWidth; }

	virtual void Bind();
	virtual void UnBind();
	virtual bool Compare(const IMaterial& material);
private:
	GLfloat m_lineWidth;
};

}

#endif LINE_MATERIAL_H
