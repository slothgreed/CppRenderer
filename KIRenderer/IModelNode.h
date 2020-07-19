#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
namespace Renderer
{
class IModelProperty;

class DLL_EXPORT IModelNode : public IObserver
{
public:
	IModelNode();
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void ShowProperty() {};
	virtual void AddPartSelect(TOPOLOGY_TYPE type, int first, int count) {};
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IModel> GetModel() { return m_pModel; }
	void SetModelMatrix(const mat4x4& matrix) { m_ModelMatrix = matrix; };
	const mat4x4& GetModelMatrix() { return m_ModelMatrix; };
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
protected:
	void AddProperty(shared_ptr<IModelProperty> prop);
	void RemoveProperty(shared_ptr<IModelProperty> prop);
	virtual void DrawProperty(shared_ptr<UniformStruct> pUniform);
	virtual void UpdateProperty();
	shared_ptr<IModel> m_pModel;

private:
	virtual void DrawCore(shared_ptr<UniformStruct> pUniform) = 0;
	bool m_visible;
	vector<shared_ptr<IModelProperty>> m_pProperty;
	mat4x4 m_ModelMatrix;
};
}
}
#endif IMODEL_NODE_H