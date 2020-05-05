#ifndef IMANIPULATOR_MODEL_H
#define IMANIPULATOR_MODEL_H

namespace KI
{
namespace Asset
{
enum MANIPULATOR_HANDLE
{
	MANIPULATOR_HANDLE_X	= 0,
	MANIPULATOR_HANDLE_Y	= 1,
	MANIPULATOR_HANDLE_Z	= 2,
	MANIPULATOR_HANDLE_NUM	= 3
};

enum MANIPULATOR_TYPE
{
	MANIPULATOR_TYPE_MOVE	= 0,
	MANIPULATOR_TYPE_SCALE	= 1,
	MANIPULATOR_TYPE_ROTATE	= 2,
	MANIPULATOR_TYPE_NUM	= 3,
};

class DLL_EXPORT IManipulatorModel : public IModel
{
public:
	virtual MODEL_TYPE Type() { return MODEL_TYPE::MODEL_TYPE_MANIPULATOR; };
	IManipulatorModel() {};
	virtual ~IManipulatorModel() {};

	virtual void Build() = 0;
	virtual void GetBDB(BDB& bdb) override { assert(0); };
	virtual void GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle) = 0;
	virtual void GetEdgeList(vector<vec3>& edgeList, vector<int>& edgeIndex, MANIPULATOR_HANDLE handle) = 0;

private:

};
}
}

#endif IMANIPULATOR_MODEL_H