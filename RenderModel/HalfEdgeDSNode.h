#ifndef HALFEDGE_DS_NODE_H
#define HALFEDGE_DS_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT HalfEdgeDSNode : public PolygonModelNode
{
public :
	HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model);
	~HalfEdgeDSNode();

	void VisibleHalfEdgeLine(bool visibility);
	void VisibleCluster(bool visible, int level);
	void VisibleTangent(bool visible);

private:
	shared_ptr<HalfEdgeResolutionProperty> m_pProperty;
	shared_ptr<VertexTangentProperty> m_pTangentProperty;

};
}
}

#endif HALFEDGE_DS_NODE_H
