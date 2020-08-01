#ifndef ROTATE_MANIPULATOR_H
#define ROTATE_MANIPULATOR_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT RotateManipulator : public IManipulatorModel
{
public:

	class ShapeData
	{
	public:
		Cylinder cylinder;
		Cone cone;
	};

	RotateManipulator();
	~RotateManipulator();

	virtual void Build() override;
	virtual void GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle) override;
private:
	ShapeData xDirection;
	ShapeData yDirection;
	ShapeData zDirection;
	
};
}
}

#endif ROTATE_MANIPULATOR_H
