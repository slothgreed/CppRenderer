#ifndef RENDER_DATA_H
#define RENDER_DATA_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT RenderData
{
public:
	RenderData() {};
	~RenderData();
	RenderData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);

	void Set(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	GLuint GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	void Draw();

private:
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
};
}
}

#endif RENDER_DATA_H