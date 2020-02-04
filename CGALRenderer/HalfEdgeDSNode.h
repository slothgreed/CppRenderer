#ifndef HALFEDGE_DS_NODE_H
#define HALFEDGE_DS_NODE_H

namespace KI
{

class HalfEdgeDSNode : public ModelNode
{
public :
	HalfEdgeDSNode(shared_ptr<HalfEdgeModel> model);
	~HalfEdgeDSNode();
private:
	void VisibleHalfEdgeLine(bool visibility);

};
}


#endif HALFEDGE_DS_NODE_H
