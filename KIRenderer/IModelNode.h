#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
namespace Renderer
{
class IModelProperty;

class DLL_EXPORT IModelNode : public IObserver, public IPickable
{
public:
	IModelNode() {};
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	virtual void ShowProperty() {};
	virtual void Draw() = 0;
	virtual void Update(void* sender, IEventArgs* args);
	shared_ptr<IModel> GetModel() { return m_pModel; }
	virtual void SetPickID(int startIndex, int& endIndex) override { assert(0); endIndex = startIndex; };

protected:
	void AddProperty(shared_ptr<IModelProperty> prop);
	void RemoveProperty(shared_ptr<IModelProperty> prop);
	virtual void DrawProperty();
	virtual void UpdateProperty();
	shared_ptr<IModel> m_pModel;

private:
	vector<shared_ptr<IModelProperty>> m_pProperty;
};
}
}
#endif IMODEL_NODE_H