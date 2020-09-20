#ifndef DEFAULT_VBO_CODE_H
#define DEFAULT_VBO_CODE_H

namespace KI
{
namespace ShaderLib
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

	void SetPlaneGLPosition(bool value) { m_planeGlPosition = value; }
	void SetWorldGLPosition(bool value) { m_worldGlPosition = value; }

	void SetPlaneOutPosition(bool value) { m_planeOutPosition = value; }
	void SetWorldOutPosition(bool value) { m_worldOutPosition = value; }

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
	bool m_planeGlPosition;	// 位置をそのままにしてgl_Positionに流すかどうか
	bool m_worldGlPosition;

	bool m_planeOutPosition;	// 位置をどのように次のシェーダステージに流すか
	bool m_worldOutPosition;

};
}
}



#endif DEFAULT_VBO_CODE_H