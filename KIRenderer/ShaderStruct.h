#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT ShaderStruct : public IShaderCode
{
	enum SHADER_STRUCT_TYPE : unsigned short
	{
		DEFAULT_UNIFORM_COLOR_TEXTURE,
		DEFAULT_UNIFORM_FIX_COLOR,
		DEFAULT_UNIFORM_NUM
	};
public:
	ShaderStruct();
	~ShaderStruct();
	virtual void Initialize(GLuint programId) override;
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk)  override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk)  override {}
	;

private:
	void BindScene(GLuint programId);
	void BindLight(GLuint programId);
};

}
}
#endif DEFAULT_SHADER_H

