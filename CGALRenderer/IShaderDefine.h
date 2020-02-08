namespace KI
{
class IShaderDefine
{
public:
	IShaderDefine() {};
	virtual ~IShaderDefine() {};
	virtual SHADER_TYPE Type() = 0;
	virtual void GetVertexDefine(string& define) = 0;
	virtual void GetFragDefine(string& define) = 0;
	virtual bool Compare(shared_ptr<IShaderDefine> shaderDefine) = 0;
private:

};
}