#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
#include <map>
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IVertexBuffer : public IAttribute
{
public:
	IVertexBuffer(const string& filePath);
	virtual ~IVertexBuffer() {};

	virtual bool NewShaderCompare(IVertexBuffer* pTarget) = 0;
	virtual void SetArrayBuffer(GLuint location, shared_ptr<ArrayBuffer> pArrayBuffer) { assert(0); };
	virtual shared_ptr<ArrayBuffer> GetArrayBuffer(GLuint location) { assert(0); return nullptr; };
	virtual void Add(GLuint location, shared_ptr<ArrayBuffer> arrayBuffer);
	virtual void Remove(GLuint location);
	virtual bool IsInstanceDraw() { return m_instanceNum > 1; };
	virtual void SetInstanceNum(int num) { m_instanceNum = num; }
	virtual void BindAttribDivisor() { assert(0); };
	virtual void UnBindAttribDivisor() { assert(0); };
	virtual void DrawByIndexBuffer(GLuint primitiveType, IndexBuffer* pIndexbuffer, GLuint first = 0, GLuint count = 0);
	virtual void Draw(GLuint primitiveType, GLuint first, GLuint count);
	virtual void Draw(GLuint primitiveType);
	GLuint GetVertexSize() { return m_VertexSize; }
	void SetVertexSize(GLuint size) { m_VertexSize = size; }
	void Dispose();

protected:
	void BindToVAO(GLuint location);
	map<GLuint, shared_ptr<ArrayBuffer>> m_VertexInfo; // int = data location;
private:
	GLuint m_VertexSize;
	GLuint m_vaoId;
	GLuint m_instanceNum;
	string m_filePath;
};
}
}
#endif IVERTEX_BUFFER_H
