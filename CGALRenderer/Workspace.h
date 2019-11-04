#ifndef WORKSPACE_H
#define WORKSPACE_H
class Camera;
class Shader;
class VertexBuffer;
class CGALPolyhedron;
class ShaderScene;
class Workspace
{
public:
	Workspace();
	~Workspace();
	void Initialize(Project* m_pProject);
	void Invoke();

	std::shared_ptr<Camera> MainCamera() { return m_pCamera; }
private:

	std::shared_ptr<Camera> m_pCamera;
	Shader* m_pDefaultShader;
	ShaderScene* m_pShaderScene;
	VertexBuffer* m_pAxis;
	CGALPolyhedron* m_pPolyhedron;
};

#endif WORKSPACE_H