#ifndef SCENE_H
#define SCENE_H
namespace KI
{
namespace Renderer
{

class DLL_EXPORT Scene
{
	friend class VisibleModelIterator;
	friend class SceneModelIterator;
public:
	Scene();
	~Scene();

	void Initialize();
	void SetCamera(shared_ptr<ICamera> pCamera) { m_pCamera = pCamera; };
	void AddModelNode(shared_ptr<IModelNode> pModelNode);
	void RemoveModelNode(shared_ptr<IModelNode> pModelNode);
	int  ModelNum() { return (int)m_pRenderList.size(); };
	void AddLight(shared_ptr<ILight> pLight);
	void RemoveLight(shared_ptr<ILight> pLight);
	const vector<shared_ptr<IModelNode>>& ModelNodes() { return m_pRenderList; };
	void Draw();
	void PickDraw(shared_ptr<IShader> pShader);
	void Bind();
	void UnBind();
	shared_ptr<ICamera> GetCamera() { return m_pCamera; };
	shared_ptr<UniformStruct> GetUniformStruct() { return m_pUniformStruct; }
	shared_ptr<IModelNode> GetObject(int objectId);
private:
	void BindLight();
	shared_ptr<ICamera> m_pCamera;
	shared_ptr<UniformStruct> m_pUniformStruct;
	vector<shared_ptr<ILight>> m_pLights;
	vector<shared_ptr<IModelNode>> m_pRenderList;
	unique_ptr<UniformBuilder> m_pUniformBuilder;
};

class DLL_EXPORT SceneModelIterator
{
public:
	SceneModelIterator(Scene* pScene) : m_pScene(pScene), m_Index(0) {};
	~SceneModelIterator() {};

	void Next();
	IModelNode& Current();
	bool HasNext();
	int Index() { return m_Index; }
private:
	Scene* m_pScene;
	int m_Index;
};

// Usecase ;
// auto itr = VisibleModelIterator(pScene);
// for(auto itr(pScene); itr.HasNext(); itr.Next())
//	auto model = itr.Current();
class DLL_EXPORT VisibleModelIterator
{
public:
	VisibleModelIterator(Scene* pScene);
	~VisibleModelIterator() {};

	void Next();
	IModelNode& Current();
	bool HasNext();
private:
	Scene* m_pScene;
	int m_NextIndex;
	IModelNode* m_pNextModel;
};
}
}
#endif SCENE_H
