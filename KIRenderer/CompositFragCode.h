#ifndef COMPOSIT_FRAG_CODE_H
#define COMPOSIT_FRAG_CODE_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT CompositFragCode : public IShaderCode
{
public:
	enum COMPOSIT_TYPE
	{
		COMPOSIT_TYPE_ADD,
		COMPOSIT_TYPE_SUB,
		COMPOSIT_TYPE_MULT,
		COMPOSIT_TYPE_OVERWRITE,
		COMPOSIT_TYPE_NUM
	};

	CompositFragCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_OUTPUT) +
			string(SHADER_EXT_FRAG)) {};
	~CompositFragCode() {};
	SHADER_TYPE Type() { return SHADER_TYPE_COMPOSIT; }
	void SetShaderDefine(CompositFragCode::COMPOSIT_TYPE type);
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	CompositFragCode::COMPOSIT_TYPE m_CompositType;

};
}
}
#endif COMPOSIT_FRAG_CODE_H
