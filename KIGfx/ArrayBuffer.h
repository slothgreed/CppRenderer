#ifndef ARRAY_BUFFER_H
#define ARRAY_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT ArrayBuffer : public IGLObject
{
public:
	ArrayBuffer();
	~ArrayBuffer();
	GLuint ID() { return m_Id; }

	virtual void Generate() override;
	void Set(const vector<vec2>& index);
	void Set(const vector<vec3>& index);
	void Set(const vector<int>& index);
	virtual void Dispose() override;
	GLuint Size() { return m_Size; }

protected:
	virtual void Bind() override;
	virtual void UnBind() override;
private:
	GLuint m_Id;
	GLuint m_Size;
};
}
}
#endif ARRAY_BUFFER_H
