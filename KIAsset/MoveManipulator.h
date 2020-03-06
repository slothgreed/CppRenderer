#ifndef MOVE_MANIPULATOR_H
#define MOVE_MANIPULATOR_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT MoveManipulator : public IManipulatorModel
{
public:

	virtual MODEL_TYPE Type() { return MODEL_TYPE::MODEL_TYPE_MOVE_MANIPULATOR; };
	class ShapeData
	{
	public:
		vector<vec3> position;
		Cone cone;
	};

	MoveManipulator();
	~MoveManipulator();

	virtual void Build() override;
	void GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle);
	void GetEdgeList(vector<vec3>& edgeList, vector<int>& edgeIndex, MANIPULATOR_HANDLE handle);
private:
	ShapeData xDirection;
	ShapeData yDirection;
	ShapeData zDirection;
	
};
}
}


#endif MOVE_MANIPULATOR_H