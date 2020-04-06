#ifndef DEFAULT_VERTEX_CODE_H
#define DEFAULT_VERTEX_CODE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultVertexCode : public IShaderCode
{
public:
	DefaultVertexCode();
	~DefaultVertexCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode);
	
	void SetOutInstance(bool value) { m_outInstance = value; }

	bool UseGBuffer() const { return m_useGBuffer; }
	bool UseNormal() const { return m_useNormal; };
	bool ViewNormal() const { return m_viewNormal; }
	bool UseColor() const { return m_useColor; };
	
	bool UseTexcoord() const { return m_useTexcoord; };
	bool UseInstance() const { return m_useInstance; };
	bool OutInstance() const { return m_outInstance; };

	void SetShaderDefine(VERTEX_LAYOUT layout);
	void SetShaderDefine(SHADER_TYPE type);
	void SetViewNormal(bool value) { m_viewNormal = value; }
private:
	bool m_useGBuffer;
	bool m_useNormal;
	bool m_planePosition;
	bool m_useColor;
	bool m_useTexcoord;
	bool m_useInstance;
	bool m_useShading;
	bool m_outInstance;
	bool m_viewNormal;
};
}
}



#endif DEFAULT_VERTEX_CODE_H