#ifndef DEFAULT_VERTEX_CODE_H
#define DEFAULT_VERTEX_CODE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultVertexCode : public IShaderCode
{
public:
	DefaultVertexCode(IVertexBuffer* pVertexBuffer);
protected:
	DefaultVertexCode(const string& shaderCode);
public:
	virtual ~DefaultVertexCode();

	virtual void Initialize(GLuint programId);
	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes) override;
	virtual shared_ptr<IShaderCode> GetVertexBufferCode(shared_ptr<IVertexBuffer> pVertexBuffer) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;
	void SetOutInstance(bool value) { m_outInstance = value; }
	void SetPlanePosition(bool value) { m_planePosition = value; }

	bool OutNormal() const { return m_outNormal; };
	bool OutColor() const { return m_outColor; };
	
	bool OutTexcoord() const { return m_outTexcoord; };
	bool OutInstance() const { return m_outInstance; };
	bool OutPlanePosition() const { return m_planePosition; };

	void SetShaderDefine(VERTEX_LAYOUT layout);
private:
	bool m_outNormal;
	bool m_planePosition;	// ˆÊ’u‚ð‚»‚Ì‚Ü‚Ü‚É‚µ‚Ägl_Position‚É—¬‚·‚©‚Ç‚¤‚©
	bool m_outColor;
	bool m_outTexcoord;
	bool m_outInstance;
};
}
}



#endif DEFAULT_VERTEX_CODE_H