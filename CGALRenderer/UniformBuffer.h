#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

class UniformBuffer
{
public:
	UniformBuffer() {};
	~UniformBuffer() {};

	virtual void Generate() {};
	virtual void Bind() {};
	virtual void UnBind() {};

private:

};


#endif UNIFORM_BUFFER_H