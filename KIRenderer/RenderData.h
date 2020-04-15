#ifndef RENDER_DATA_H
#define RENDER_DATA_H

namespace KI
{
namespace Renderer
{
class RenderData
{
public:
	RenderData(GLuint m_primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer);
	~RenderData();

private:
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
};
}
}

#endif RENDER_DATA_H