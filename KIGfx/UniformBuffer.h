#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT UniformBuffer : public GLObject
{
public:
	UniformBuffer(GLuint dataLocation);
	~UniformBuffer();
	virtual void Generate() override;
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual void Dispose() override;
private:
	GLuint m_dataLocation;
};
}
}
#endif UNIFORM_BUFFER_H