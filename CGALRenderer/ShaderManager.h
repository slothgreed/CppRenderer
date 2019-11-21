#ifndef SHADER_MANAGER_H
namespace KI
{
struct ShaderBuildInfo;
class IShader;
class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager* Instance();
	shared_ptr<IShader> FindOrNew(const ShaderBuildInfo& buildInfo);
	void Dispose();
private:
	shared_ptr<IShader> Generate(const ShaderBuildInfo& buildInfo);
	vector<shared_ptr<IShader>> m_pShaderList;
	static ShaderManager* m_Instance;
};
}
#endif // !SHADER_MANAGER_H
