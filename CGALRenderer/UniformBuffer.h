#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H
namespace KI
{
class UniformBuffer
{
public:
	UniformBuffer() {};
	~UniformBuffer() {};

	virtual void Generate() {};
	virtual void Bind() {};
	virtual void UnBind() {};
	virtual void Dispose() {};

private:

};
}

#endif UNIFORM_BUFFER_H