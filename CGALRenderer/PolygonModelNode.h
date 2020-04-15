#ifndef MODEL_NODE_H
#define MODEL_NODE_H
namespace KI
{
class PolygonModelNode : public IModelNode
{
public:
	PolygonModelNode(shared_ptr<IModel> model);
	~PolygonModelNode();
	virtual void Draw() override;
	virtual void ShowProperty() override;
	virtual void Update(void* sender, IEventArgs* args) override;
	IPolygonModel* GetModel();
	virtual void SetPickID(int startIndex, int& endIndex) override;


	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
	void VisibleFace(bool visibility);
	void VisibleEdge(bool visibility);
	shared_ptr<IVertexBuffer> GetVertexBuffer() { return m_pFaceBuffer; }
protected:
	string m_name;
	shared_ptr<IMaterial> m_pFaceMaterial;
	shared_ptr<IMaterial> m_pEdgeMaterial;
	shared_ptr<IVertexBuffer> m_pFaceBuffer;
	shared_ptr<IndexBuffer> m_pFaceIndex;
	shared_ptr<IVertexBuffer> m_pEdgeBuffer;

private:
	shared_ptr<DefaultVertexBuffer> m_pPickPolygon;
	BDB m_bdb;
	void SetRenderData();
};

}

#endif MODEL_NODE_H
