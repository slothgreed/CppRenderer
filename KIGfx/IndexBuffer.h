#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void Generate();
	bool IsGenerated();
	void Set(GLuint primitiveType, const vector<int>& index);
	void Dispose();
	void Draw();
	GLuint Size() { return m_indexSize; }
	GLuint m_PrimitiveType;
	GLuint m_Id;
	GLuint m_indexSize;
};
}
}
#endif INDEX_BUFFER_H
