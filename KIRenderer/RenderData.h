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
	RenderData(PRIM_TYPE primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);

	class DLL_EXPORT RenderRegion
	{
	public:
		shared_ptr<IShading> m_pShading;
		string m_descriptor;
		int m_first;
		int m_count;
	};
	void SetShading(shared_ptr<IShading> pShading);
	void SetGeometryData(PRIM_TYPE primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer = nullptr);
	PRIM_TYPE GetPrimitiveType() { return m_pPrimitiveType; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	shared_ptr<IndexBuffer> GetIndexBuffer() { return m_pIndexBuffer; }
	shared_ptr<IShading> GetShading() { return m_pShading; }
	void AddRenderRegion(const string& descriptor, shared_ptr<IShading> pShading, int first, int count);
	bool HasRenderRegion() { return m_pRenderRegion.size() != 0; };
	void ClearRenderRegion();
	//void Draw();
	void Draw(const shared_ptr<UniformStruct> pUniform);
	void Draw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniform, int first = -1, int count = -1);
	shared_ptr<RenderData> Clone();


private:
	void FindOrNewShader(shared_ptr<IShading> pShading);
	void DrawUseRegion(const shared_ptr<UniformStruct> pUniform);
	bool m_bRecompileShader;
	shared_ptr<IShader> m_pShader;
	int GetVertexSize();
	PRIM_TYPE	m_pPrimitiveType;
	shared_ptr<IndexBuffer> m_pIndexBuffer;
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShading> m_pShading;
	vector<RenderRegion> m_pRenderRegion;
};
}
}

#endif RENDER_DATA_H