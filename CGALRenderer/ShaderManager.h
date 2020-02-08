#ifndef SHADER_MANAGER_H
namespace KI
{
class IShaderDefine;
class IShader;
class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* Instance();
	shared_ptr<IShader> FindOrNew(shared_ptr<IShaderDefine> shaderDefine);
	void Dispose();
private:
	shared_ptr<IShader> Generate(shared_ptr<IShaderDefine> shaderDefine);
	vector<shared_ptr<IShader>> m_pShaderList;
	static ShaderManager* m_Instance;
};
}
#endif // !SHADER_MANAGER_H
