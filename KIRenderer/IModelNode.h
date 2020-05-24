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
	IModelNode() {};
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	void Draw();
	virtual void ShowProperty() {};
	virtual void AddPartSelect(TOPOLOGY_TYPE type, int first, int count) {};
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IModel> GetModel() { return m_pModel; }
	void SetVisible(bool value) { m_visible = value; }
	bool Visible() { return m_visible; }
protected:
	void AddProperty(shared_ptr<IModelProperty> prop);
	void RemoveProperty(shared_ptr<IModelProperty> prop);
	virtual void DrawProperty();
	virtual void UpdateProperty();
	shared_ptr<IModel> m_pModel;

private:
	virtual void DrawCore() = 0;
	bool m_visible;
	vector<shared_ptr<IModelProperty>> m_pProperty;
};
}
}
#endif IMODEL_NODE_H