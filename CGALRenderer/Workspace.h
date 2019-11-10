#ifndef WORKSPACE_H
#define WORKSPACE_H
class Camera;
class IShader;
class VertexBuffer;
class UniformScene;
class UniformBuffer;
class ModelNode;
class Workspace
{
public:
	Workspace();
	~Workspace();
	void Initialize(Project* m_pProject);
	void Invoke();
	void ShowProperty();

	std::shared_ptr<Camera> MainCamera() { return m_pCamera; }
private:

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<IShader> m_pDefaultShader;
	std::shared_ptr<UniformScene> m_pUniformScene;
	std::vector<std::shared_ptr<ModelNode>> m_pRenderList;
	
};

#endif WORKSPACE_H