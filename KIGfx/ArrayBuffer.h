#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT ArrayBuffer : public IGLObject
{
public:
	ArrayBuffer(GLuint componentType, GLuint componentSize);
	~ArrayBuffer();

	virtual void Generate() override;
	void Set(const vector<vec2>& index);
	void Set(const vector<vec3>& index);
	void Set(const vector<int>& index);
	virtual void Dispose() override;
	GLuint Size() { return m_Size; }
	GLuint ComponentSize() { return m_ComponentSize; }
	GLuint ComponentType() { return m_ComponentType; }
protected:
	virtual void Bind() override;
	virtual void UnBind() override;
private:
	GLuint m_ComponentType;
	GLuint m_ComponentSize;
	GLuint m_Size;

};
}
}
#endif ARRAY_BUFFER_H
