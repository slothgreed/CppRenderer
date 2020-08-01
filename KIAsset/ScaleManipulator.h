#ifndef SCALE_MANIPULATOR_H
#define SCALE_MANIPULATOR_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT ScaleManipulator : public IManipulatorModel
{
public:

	class ShapeData
	{
	public:
		Cylinder cylinder;
		Cube cube;
	};

	ScaleManipulator();
	~ScaleManipulator();

	virtual void Build() override;
	virtual void GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle) override;
private:
	ShapeData xDirection;
	ShapeData yDirection;
	ShapeData zDirection;
	
};
}
}

#endif SCALE_MANIPULATOR_H
