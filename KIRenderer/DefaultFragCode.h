#ifndef DEFAULT_FRAG_CODE_H
#define DEFAULT_FRAG_CODE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT DefaultFragCode : public IShaderCode
{
public:
	DefaultFragCode();
	~DefaultFragCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode);
	void SetUseGBuffer(bool value)	{ m_useGBuffer = value; }
	void SetUseNormal(bool value)	{ m_useNormal = value; }
	void SetUseColor(bool value)	{ m_useColor = value; }
	void SetUseTexcoord(bool value) { m_useTexcoord = value; }
	void SetUseTexture0(bool value) { m_useTexture0 = value; }
	void SetShading(bool value)		{ m_useShading = value; }

	bool UseGBuffer() const		{ return m_useGBuffer; }
	bool UseNormal() const		{ return m_useNormal; }
	bool UseColor() const		{ return m_useColor; }
	bool UseTexcoord() const	{ return m_useTexcoord; }
	bool UseTexture0() const	{ return m_useTexture0; }
	bool UseShading() const		{ return m_useShading; }

	void SetShaderDefine(VERTEX_LAYOUT layout);

private:
	bool m_useGBuffer;
	bool m_useNormal;
	bool m_useColor;
	bool m_useTexcoord;
	bool m_useTexture0;
	bool m_useShading;
};
}
}



#endif DEFAULT_FRAG_CODE_H