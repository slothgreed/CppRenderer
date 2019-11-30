#ifndef POINT_MATERIAL_H

namespace KI
{

class PointMaterial : public DefaultMaterial
{
public:
	PointMaterial();
	~PointMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE_POINTMATERIAL; }
	void SetPointSize(GLuint value) { m_pointSize = value; }
	GLuint GetPointSize() { return m_pointSize; }
	GLuint const GetPointSize() const { return m_pointSize; }

	virtual void Bind();
	virtual void UnBind();

	virtual bool Compare(const IMaterial& material);

private:
	GLuint m_pointSize;
};

}


#define POINT_MATERIAL_H
#endif POINT_MATERIAL_H