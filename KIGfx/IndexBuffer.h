#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IndexBuffer : public IGLObject
{
public:
	IndexBuffer();
	~IndexBuffer();
	virtual void Generate() override;
	void Set(GLuint primitiveType, const vector<int>& index);
	virtual void Dispose() override;
	void Draw();
	GLuint Size() { return m_indexSize; }

protected:
	virtual void Bind() override;
	virtual void UnBind() override;
private:
	GLuint m_PrimitiveType;
	GLuint m_indexSize;
};
}
}
#endif INDEX_BUFFER_H
