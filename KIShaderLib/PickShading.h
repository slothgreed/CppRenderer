#ifndef PICK_SHADING_H
#define PICK_SHADING_H

namespace KI
{
namespace ShaderLib
{

class PickFragCode : public IShaderCode
{
public:
	PickFragCode();
	~PickFragCode();
	const int PICK_SHADING_PICK_ID = 0;

	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;

private:

};

class DLL_EXPORT PickShading : public IShading
{
public:
	PickShading();
	~PickShading() {};

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type) override;

private:

};

}
}

#endif PICK_SHADING_H
