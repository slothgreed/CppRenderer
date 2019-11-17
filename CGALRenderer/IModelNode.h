#ifndef IMODEL_NODE_H
#define IMODEL_NODE_H

class IObserver;
class IModelNode : public IObserver
{
public:
	IModelNode() {};
	~IModelNode() {};

	virtual void ShowProperty() = 0;
	virtual void Draw() = 0;
	virtual void Update(void* sender, shared_ptr<EventArgs> args) {};
	
private:
};

#endif IMODEL_NODE_H