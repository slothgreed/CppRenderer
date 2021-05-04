#ifndef ISHADER_BUILD_INFO_H
#define	ISHADER_BUILD_INFO_H
namespace KI
{
namespace Gfx
{
class VertexBuffer;
class DLL_EXPORT IShaderBuildInfo
{
public:
	IShaderBuildInfo();
	~IShaderBuildInfo();

	void SetVertexBuffer(shared_ptr<VertexBuffer> pVertexBuffer) { m_pVertexBuffer = pVertexBuffer; }
	shared_ptr<VertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	void SetShaderChunk(shared_ptr<IShaderChunk> value) { m_pShaderChunk = value; };
	shared_ptr<IShaderChunk> GetShaderChunk() { return m_pShaderChunk; };
	bool Compare(IShaderBuildInfo* pShaderBuildInfo);
private:
	shared_ptr<VertexBuffer> m_pVertexBuffer;
	shared_ptr<IShaderChunk> m_pShaderChunk;
};

}
}
#endif // !IRENDERTARGET_H