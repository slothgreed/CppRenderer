#ifndef CGAL_MODEL_NODE_H
#define CGAL_MODEL_NODE_H

class IModelNode;
class IShader;
class VertexBuffer;
class IModelProperty;
class CGALModelNode : public IModelNode
{
public:
	CGALModelNode(shared_ptr<IModel> model);
	~CGALModelNode();
	virtual void Draw();
	virtual void ShowProperty();
	virtual void Update(void* sender, shared_ptr<EventArgs> args);

	void SetBDB(BDB bdb);
private:
	string m_name;
	shared_ptr<IShader> m_pFaceShader;
	shared_ptr<VertexBuffer> m_pFaceBuffer;

	shared_ptr<IShader> m_pEdgeShader;
	shared_ptr<VertexBuffer> m_pEdgeBuffer;
	shared_ptr<IModel> m_pModel;
	vector<shared_ptr<IModelProperty>> m_pProperty;
	BDB m_bdb;
	void SetRenderData();
};



#endif CGAL_MODEL_NODE_H
