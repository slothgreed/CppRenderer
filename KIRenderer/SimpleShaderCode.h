#ifndef SIMPLE_SHADER_CODE_H
#define SIMPLE_SHADER_CODE_H


class DLL_EXPORT PickFragCode : public IShaderCode
{
public:
	PickFragCode()
		: IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_PICK) +
			string(SHADER_EXT_FRAG)) {};
	~PickFragCode() {};

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_BEZIERLINE; }
};



#endif SIMPLE_SHADER_CODE_H