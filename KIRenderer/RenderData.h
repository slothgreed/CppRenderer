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

	void SetMaterial(shared_ptr<IMaterial> pMaterial);
	void SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	GLuint GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	shared_ptr<IMaterial> GetMaterial() { return m_pMaterial; }
	void Draw();
	void Draw(shared_ptr<IShader> pShader);
	shared_ptr<RenderData> Clone();

private:
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IMaterial> m_pMaterial;
};
}
}

#endif RENDER_DATA_H