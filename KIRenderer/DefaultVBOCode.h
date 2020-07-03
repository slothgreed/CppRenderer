#ifndef DEFAULT_VBO_CODE_H
#define DEFAULT_VBO_CODE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultVBOCode : public IShaderCode
{
public:
	DefaultVBOCode(IVertexBuffer* pVertexBuffer);
public:
	virtual ~DefaultVBOCode();

	virtual void Initialize(GLuint programId) {};
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes);

	void SetPlanePosition(bool value) { m_planePosition = value; }


	bool InNormal() const	{ return m_inNormal; };
	bool InColor() const	{ return m_inColor; };
	bool InTexcoord() const { return m_inTexcoord; };
	bool InInstance() const { return m_inInstance; };

	void SetShaderDefine(VERTEX_LAYOUT layout);
private:
	bool m_inNormal;
	bool m_inColor;
	bool m_inTexcoord;
	bool m_inInstance;
	bool m_planePosition;	// ˆÊ’u‚ð‚»‚Ì‚Ü‚Ü‚É‚µ‚Ägl_Position‚É—¬‚·‚©‚Ç‚¤‚©
};
}
}



#endif DEFAULT_VBO_CODE_H