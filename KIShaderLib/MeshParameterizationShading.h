#ifndef MESH_PARAMETERIZATION_SHADING_H
#define MESH_PARAMETERIZATION_SHADING_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT MeshParameterizationShading : public IShading
{
public:
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_MESH_PARAMETERIZATION; }

	MeshParameterizationShading();
	~MeshParameterizationShading() {};

	virtual bool NewShaderCompare(IShaderChunk* pTarget) override;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;
private:
};

class DLL_EXPORT MeshParameterizationGeomCode : public IShaderCode
{

public:

	MeshParameterizationGeomCode();
	~MeshParameterizationGeomCode();

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_MESH_PARAMETERIZATION; }

	virtual void Initialize(GLuint programId) override;

	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes);
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};

private:
};

class DLL_EXPORT MeshParameterizationVertCode : public IShaderCode
{
public:

	MeshParameterizationVertCode();
	~MeshParameterizationVertCode() {};

	enum ATTRIBUTE
	{
		POSITION = 0,
		NORMAL	= 1,
		TANGENT = 2,
		UV		= 3
	};


	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_MESH_PARAMETERIZATION; }

	virtual void Initialize(GLuint programId) override {};

	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};

private:
};
class DLL_EXPORT MeshParameterizationFragCode : public IShaderCode
{

public:

	MeshParameterizationFragCode();
	~MeshParameterizationFragCode() {};

	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_MESH_PARAMETERIZATION; }

	virtual void Initialize(GLuint programId) override {};

	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override {};

private:
};

}
}
#endif MESH_PARAMETERIZATION_SHADING_H