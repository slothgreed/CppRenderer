#ifndef ISHADER_BUILD_INFO_H
#define	ISHADER_BUILD_INFO_H
namespace KI
{
namespace Gfx
{
class IVertexBuffer;
class DLL_EXPORT IShaderBuildInfo
{
public:
	IShaderBuildInfo();
	~IShaderBuildInfo();

	void SetVertexBuffer(shared_ptr<IVertexBuffer> pVertexBuffer) { m_pVertexBuffer = pVertexBuffer; }
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pVertexBuffer; }
	void SetShaderChunk(shared_ptr<IShaderChunk> value) { m_pShaderChunk = value; };
	shared_ptr<IShaderChunk> GetShaderChunk() { return m_pShaderChunk; };
	bool Compare(IShaderBuildInfo* pShaderBuildInfo);
private:
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShaderChunk> m_pShaderChunk;
};

}
}
#endif // !IRENDERTARGET_H