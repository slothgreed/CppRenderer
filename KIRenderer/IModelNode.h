#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
namespace Renderer
{
class IModelProperty;
class RenderData;

class DLL_EXPORT PropertyIterator : IIterator<IModelProperty*>
{
public:
	PropertyIterator(IModelNode* pNode);

	virtual bool HasNext();
	virtual void Next();
	virtual IModelProperty* Current();

private:
	IModelNode*	m_pNode;
	int m_index;
};

class Scene;
class DLL_EXPORT IModelNode : public IObserver
{
public:
	friend class PropertyIterator;
	IModelNode();
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	virtual void FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniformStorage);
	void Draw(shared_ptr<UniformStruct> pUniform);
	
	virtual void ClearSelect() {};
	virtual void AddSelect(PICK_TYPE type, shared_ptr<IShading> pShader, int index, int first, int count);
	virtual void Update(void* sender, IEventArgs* args);
	const shared_ptr<IModel> GetModel() { return m_pModel; }
	void SetModelMatrix(const mat4x4& matrix) { m_ModelMatrix = matrix; };
	const mat4x4& GetModelMatrix() const { return m_ModelMatrix; };
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
	void AddPickID(int start, int* next);
	bool HasPickID(int index);
	int GetRenderDataNum() { return (int)m_pRenderData.size(); }
	shared_ptr<RenderData> GetRenderData(int id);
protected:
	void AddProperty(shared_ptr<IModelProperty> prop, IPropertyArgs* propArgs);
	bool HasProperty(unsigned int type);
	shared_ptr<IModelProperty> GetProperty(unsigned int type);
	void RemoveProperty(shared_ptr<IModelProperty> prop);
	virtual void DrawProperty(shared_ptr<UniformStruct> pUniform);
	virtual void UpdateProperty(void* sender, IEventArgs* args);
	shared_ptr<IModel> m_pModel;
	virtual void BindModel(shared_ptr<UniformStruct> pUniform, int index);
	virtual void UnBindModel(shared_ptr<UniformStruct> pUniform, int index);
	void AddRenderData(int id, shared_ptr<RenderData> pRenderData);
	void RemoveRenderData(int id, shared_ptr<RenderData> pRenderData);

	virtual void PreDraw(shared_ptr<UniformStruct> pUniform, int index) {};
	virtual void PostDraw(shared_ptr<UniformStruct> pUniform, int index) {};
private:

	struct RenderDataInfo
	{
		RenderDataInfo() :visible(true), pRenderData(nullptr) {}
		RenderDataInfo(shared_ptr<RenderData> pData):visible(true),pRenderData(pData) {}
		bool visible;
		shared_ptr<RenderData> pRenderData;
	};


	map<int, RenderDataInfo> m_pRenderData;
	bool m_visible;
	vector<shared_ptr<IModelProperty>> m_pProperty;
	mat4x4 m_ModelMatrix;
};
}
}
#endif IMODEL_NODE_H