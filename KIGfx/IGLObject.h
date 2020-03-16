#ifndef GLBUFFER_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT IGLObject
{
public:
	IGLObject() { m_Id = 0; m_modifing = false; };
	~IGLObject() {};

	GLuint ID() { return m_Id; }
	bool IsGenerated() { return m_Id != 0; }
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
}
#endif // !GLBUFFER_H

