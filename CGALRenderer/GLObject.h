#ifndef GLBUFFER_H

class GLObject
{
public:
	GLObject() { m_Id = 0; };
	~GLObject() {};

	virtual void Generate() = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual void Dispose() = 0;

protected:
	GLuint m_Id;
};

#endif // !GLBUFFER_H

