#ifndef GET_COLOR_CODE_H
#define GET_COLOR_CODE_H
namespace KI
{
namespace ShaderLib
{

enum SHADING_COLOR_TYPE : unsigned int
{
	SHADING_COLOR_TYPE_VERTEXCOLOR,	// 頂点色
	SHADING_COLOR_TYPE_FIXCOLOR,		// 固定色
	SHADING_COLOR_TYPE_TEXTURE,		// テクスチャ色
	SHADING_COLOR_TYPE_NUM,
};

class DLL_EXPORT GetColorCode : public IShaderCode
{
public:
	GetColorCode(SHADING_COLOR_TYPE type);
	~GetColorCode();
	virtual void Initialize(GLuint programId);
	virtual void GetDefineCode(string& code);
	virtual bool Compare(IShaderCode* pShaderCode);
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform);
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform);
	SHADING_COLOR_TYPE Type() { return m_Type; }

private:
	SHADING_COLOR_TYPE m_Type;
};

}
}

#endif //GET_COLOR_CODE_H
