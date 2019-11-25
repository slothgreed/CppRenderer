#ifndef GLBUFFER_H

class GLObject
{
public:
	GLObject() { m_Id = 0; };
	~GLObject() { Dispose(); };

	virtual void Generate() = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual void Dispose() { assert(0); };

protected:
	GLuint m_Id;
};

#endif // !GLBUFFER_H

