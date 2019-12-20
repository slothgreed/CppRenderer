#ifndef GLBUFFER_H

namespace KI
{

class GLObject
{
public:
	GLObject() { m_Id = 0; m_modifing = false; };
	~GLObject() {};

	GLuint ID() { return m_Id; }
	virtual void Begin();
	virtual void End();
	virtual void Generate() = 0;
	virtual void Dispose() = 0;

protected:
	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	GLuint m_Id;
	bool m_modifing;
};

}
#endif // !GLBUFFER_H

