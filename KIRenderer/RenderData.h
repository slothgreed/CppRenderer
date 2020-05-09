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
		shared_ptr<IShaderPass> m_pShaderPass;
		string m_descriptor;
		int m_first;
		int m_count;
	};
	void SetShaderPass(shared_ptr<IShaderPass> pShaderPass);
	void SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	GLuint GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	shared_ptr<IShaderPass> GetShaderPass() { return m_pShaderPass; }
	void AddRenderRegion(const string& descriptor, shared_ptr<IShaderPass> pShaderPass, int first, int count);
	bool HasRenderRegion() { return m_pRenderRegion.size() != 0; };
	void ClearRenderRegion();
	void Draw();
	void DrawInternal(shared_ptr<IShaderPass> pShaderPass, int first, int count);
	void DrawUseRegion();
	shared_ptr<RenderData> Clone();

private:
	int GetVertexSize();
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShaderPass> m_pShaderPass;
	vector<RenderRegion> m_pRenderRegion;
};
}
}

#endif RENDER_DATA_H