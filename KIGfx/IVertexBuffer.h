#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
#include <map>
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IVertexBuffer
{
public:
	IVertexBuffer();
	~IVertexBuffer() {};

	virtual SHADER_TYPE Type() = 0;
	virtual void Add(GLuint location, shared_ptr<ArrayBuffer> arrayBuffer);
	virtual void Remove(GLuint location);
	virtual bool IsInstanceDraw() { return m_isInstanceDraw; };
	virtual void SetInstanceDraw(bool value) { m_isInstanceDraw = value; }
	virtual void BindAttribDivisor() { assert(0); };
	virtual void UnBindAttribDivisor() { assert(0); };
	virtual void Draw(IndexBuffer* pIndexbuffer);
	virtual void Draw(GLuint primitiveType, GLuint first, GLuint count);
	virtual void Draw();
	void SetPrimitiveType(GLuint primitiveType);
	GLuint Size() { return m_Size; }
	void SetVertexSize(GLuint size) { m_Size = size; }
	void Dispose();

protected:
	void BindToVAO(GLuint location);
	map<GLuint, shared_ptr<ArrayBuffer>> m_VertexInfo; // int = data location;
private:
	GLuint m_PrimitiveType;
	GLuint m_Size;
	GLuint m_vaoId;
	bool m_isInstanceDraw;
};
}
}
#endif IVERTEX_BUFFER_H
