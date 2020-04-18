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
	virtual void CalculatePickID(int startIndex, int& nextStartIndex) override;
	virtual void PickDraw() override;


	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
	void VisibleFace(bool visibility);
	void VisibleEdge(bool visibility);
	shared_ptr<IVertexBuffer> GetVertexBuffer();
protected:
	string m_name;
	shared_ptr<IMaterial> m_pFaceMaterial;
	shared_ptr<IMaterial> m_pEdgeMaterial;
	shared_ptr<RenderData> m_pFaceData;
	shared_ptr<RenderData> m_pEdgeData;

private:
	BDB m_bdb;
	void SetRenderData();
};

}

#endif MODEL_NODE_H
