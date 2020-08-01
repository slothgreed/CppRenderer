#ifndef MOVE_MANIPULATOR_H
#define MOVE_MANIPULATOR_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT MoveManipulator : public IManipulatorModel
{
public:

	class ShapeData
	{
	public:
		Cylinder cylinder;
		Cone cone;
	};

	MoveManipulator();
	~MoveManipulator();

	virtual void Build() override;
	virtual void GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle) override;
private:
	ShapeData xDirection;
	ShapeData yDirection;
	ShapeData zDirection;
	
};
}
}


#endif MOVE_MANIPULATOR_H