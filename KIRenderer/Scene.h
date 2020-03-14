#ifndef SCENE_H
#define SCENE_H
namespace KI{
namespace Renderer
{
class DLL_EXPORT Scene
{
public:
	Scene();
	~Scene();

	void Initialize();
	void SetCamera(shared_ptr<ICamera> pCamera) { m_pCamera = pCamera; };
	void AddModelNode(shared_ptr<IModelNode> pModelNode);
	void RemoveModelNode(shared_ptr<IModelNode> pModelNode);
	void AddLight(shared_ptr<ILight> pLight);
	void RemoveLight(shared_ptr<ILight> pLight);
	void Draw();
	void Bind();
	void UnBind();
private:
	shared_ptr<ICamera> m_pCamera;
	shared_ptr<UniformScene> m_pUniformScene;
	shared_ptr<UniformLight> m_pUniformLight;
	vector<shared_ptr<ILight>> m_pLights;
	vector<shared_ptr<IModelNode>> m_pRenderList;
};
}
}
#endif SCENE_H
