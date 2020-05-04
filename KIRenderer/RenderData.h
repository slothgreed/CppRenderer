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

	class DLL_EXPORT RenderRegion
	{
	public:
		shared_ptr<IMaterial> m_pMaterial;
		string m_descriptor;
		int m_first;
		int m_count;
	};
	void SetMaterial(shared_ptr<IMaterial> pMaterial);
	void SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	GLuint GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	shared_ptr<IMaterial> GetMaterial() { return m_pMaterial; }
	void AddRenderRegion(const string& descriptor, shared_ptr<IMaterial> pMaterial, int first, int count);
	bool HasRenderRegion() { return m_pRenderRegion.size() != 0; };
	void ClearRenderRegion();
	void Draw();
	void DrawInternal(shared_ptr<IMaterial> pMaterial, int first, int count);
	void DrawUseRegion();
	shared_ptr<RenderData> Clone();

private:
	int GetVertexSize();
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IMaterial> m_pMaterial;
	vector<RenderRegion> m_pRenderRegion;
};
}
}

#endif RENDER_DATA_H