#ifndef DEFAULT_VERTEX_CODE_H
#define DEFAULT_VERTEX_CODE_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT DefaultVertexCode : public IShaderCode
{
public:
	DefaultVertexCode(VERTEX_LAYOUT outLayout);
protected:
	DefaultVertexCode(const string& shaderCode);
public:
	virtual ~DefaultVertexCode();

	virtual void Initialize(GLuint programId);
	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes) override;
	virtual shared_ptr<IShaderCode> GetVertexBufferCode(shared_ptr<IVertexBuffer> pVertexBuffer) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	void SetOutInstance(bool value) { m_outInstance = value; }
	void SetPlanePosition(bool value) { m_planePosition = value; }
	void SetWorldPosition(bool value) { m_worldPosition = value; }
	void SetOutPosition(bool value) { m_outPosition = value; }

	bool OutPosition() const { return m_outPosition; }
	bool OutNormal() const { return m_outNormal; };
	bool OutColor() const { return m_outColor; };
	
	bool OutTexcoord() const { return m_outTexcoord; };
	bool OutInstance() const { return m_outInstance; };
	bool OutPlanePosition() const { return m_planePosition; };
	bool OutWorldPosition() const { return m_worldPosition; };

	void SetShaderDefine(VERTEX_LAYOUT layout);
private:
	bool m_outPosition;
	bool m_outNormal;
	bool m_planePosition;	// ˆÊ’u‚ð‚»‚Ì‚Ü‚Ü‚É‚µ‚Ägl_Position‚É—¬‚·‚©‚Ç‚¤‚©
	bool m_worldPosition;	// ˆÊ’u‚ð‚»‚Ì‚Ü‚Ü‚É‚µ‚Ägl_Position‚É—¬‚·‚©‚Ç‚¤‚©
	bool m_outColor;
	bool m_outTexcoord;
	bool m_outInstance;
};
}
}



#endif DEFAULT_VERTEX_CODE_H