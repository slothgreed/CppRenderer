namespace KI
{
namespace Gfx
{
class DLL_EXPORT IShaderDefine
{
public:
	IShaderDefine() {};
	virtual ~IShaderDefine() {};
	virtual SHADER_TYPE Type() = 0;
	virtual void GetVertexDefine(string& define) = 0;
	virtual void GetFragDefine(string& define) = 0;
	virtual bool Compare(IShaderDefine* shaderDefine) = 0;
private:

};
}
}