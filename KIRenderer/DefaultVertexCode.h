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
	bool UseGBuffer() const { return m_useGBuffer; }
	bool UseNormal() const { return m_useNormal; };
	bool UseColor() const { return m_useColor; };
	bool UseTexcoord() const { return m_useTexcoord; };
	bool UseInstance() const { return m_useInstance; };

	void SetShaderDefine(VERTEX_LAYOUT layout);

private:
	bool m_useGBuffer;
	bool m_useNormal;
	bool m_useColor;
	bool m_useTexcoord;
	bool m_useInstance;
	bool m_useShading;
};
}
}



#endif DEFAULT_VERTEX_CODE_H