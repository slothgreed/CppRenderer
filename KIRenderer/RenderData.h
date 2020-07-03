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
		shared_ptr<IShading> m_pShading;
		string m_descriptor;
		int m_first;
		int m_count;
	};
	void SetShading(shared_ptr<IShading> pShading);
	void SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	GLuint GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	shared_ptr<IShading> GetShading() { return m_pShading; }
	void AddRenderRegion(const string& descriptor, shared_ptr<IShading> pShading, int first, int count);
	bool HasRenderRegion() { return m_pRenderRegion.size() != 0; };
	void ClearRenderRegion();
	//void Draw();
	void Draw(const shared_ptr<IUniformStorage> pUniform);
	void DrawInternal(shared_ptr<IShading> pShaderPass,shared_ptr<IUniformStorage> pUniform, int first, int count);
	void DrawUseRegion(const shared_ptr<IUniformStorage> pUniform);
	shared_ptr<RenderData> Clone();

private:
	bool m_bRecompileShader;
	shared_ptr<IShader> m_pShader;
	int GetVertexSize();
	GLuint	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShading> m_pShading;
	vector<RenderRegion> m_pRenderRegion;
};
}
}

#endif RENDER_DATA_H