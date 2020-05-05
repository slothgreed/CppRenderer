namespace KI
{
namespace Asset
{
MoveManipulator::MoveManipulator()
{
}

MoveManipulator::~MoveManipulator()
{
}

void MoveManipulator::Build()
{
	vector<vec3> position;
	// x axis
	xDirection.position.push_back(vec3(0, 0, 0));
	xDirection.position.push_back(vec3(1, 0, 0));
	xDirection.cone.Build(1, 1, 10);
	mat4x4 xMatrix = mat4x4(1);
	xMatrix = glm::translate(xMatrix, vec3(1, 0, 0));
	xMatrix = glm::scale(xMatrix, vec3(0.1f));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.cone.Multi(xMatrix);

	// y axis
	yDirection.position.push_back(vec3(0, 0, 0));
	yDirection.position.push_back(vec3(0, 1, 0));
	yDirection.cone.Build(1, 1, 10);
	mat4x4 yMatrix = mat4x4(1);
	yMatrix = glm::translate(yMatrix, vec3(0, 1, 0));
	yMatrix = glm::scale(yMatrix, vec3(0.1f));
	yDirection.cone.Multi(yMatrix);

	// z axis
	zDirection.position.push_back(vec3(0, 0, 0));
	zDirection.position.push_back(vec3(0, 0, 1));
	zDirection.cone.Build(1, 1, 10);
	mat4x4 zMatrix = mat4x4(1);
	zMatrix = glm::translate(zMatrix, vec3(0, 0, 1));
	zMatrix = glm::scale(zMatrix, vec3(0.1f));
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.cone.Multi(zMatrix);
}

void MoveManipulator::GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle)
{
	if (handle == MANIPULATOR_HANDLE_X)
	{
		faceList = xDirection.cone.Position();
		faceIndex = xDirection.cone.Index();
	}
	else if (handle == MANIPULATOR_HANDLE_Y) 
	{
		faceList = yDirection.cone.Position();
		faceIndex = yDirection.cone.Index();
	}
	else if (handle == MANIPULATOR_HANDLE_Z) 
	{
		faceList = zDirection.cone.Position();
		faceIndex = zDirection.cone.Index();
	}
	else
	{
		assert(0);
	}
}

void MoveManipulator::GetEdgeList(vector<vec3>& edgeList, vector<int>& edgeIndex, MANIPULATOR_HANDLE handle)
{
	if (handle == MANIPULATOR_HANDLE_X)
	{
		edgeList = xDirection.position;
		edgeIndex.push_back(0); edgeIndex.push_back(1);
	}
	else if (handle == MANIPULATOR_HANDLE_Y)
	{
		edgeList = yDirection.position;
		edgeIndex.push_back(0); edgeIndex.push_back(1);
	}
	else if (handle == MANIPULATOR_HANDLE_Z)
	{
		edgeList = zDirection.position;
		edgeIndex.push_back(0); edgeIndex.push_back(1);
	}
	else
	{
		assert(0);
	}
}
}
}