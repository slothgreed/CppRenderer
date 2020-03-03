#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H
namespace KI
{
class IModelProperty;

class PickResult
{
public:
	PickResult() {};
	~PickResult() {};

private:

};

class IModelNode : public IObserver
{
public:
	IModelNode() {};
	IModelNode(shared_ptr<IModel> model);
	virtual ~IModelNode();

	virtual void ShowProperty() = 0;
	virtual void Pick(const vec3& direction, PickResult& result) = 0;
	virtual void Draw() = 0;
	virtual void Update(void* sender, IEventArgs* args);

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
#endif IMODEL_NODE_H