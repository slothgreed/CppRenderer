#ifndef MOVE_MANIPULATOR_H
#define MOVE_MANIPULATOR_H

namespace KI
{

class MoveManipulator : IModel
{
public:
	MoveManipulator();
	~MoveManipulator();

	virtual void Build() override;
	virtual bool HasVertexList() override { return true; };
	virtual void GetVertexList(vector<Vertex>& vertex);
	virtual void GetEdgeIndexList(vector<int>& index);
	virtual void GetFaceIndexList(vector<int>& index);
private:

};

}


#endif MOVE_MANIPULATOR_H