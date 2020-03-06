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
	ShapeData* shape = nullptr;
	if (handle == MANIPULATOR_HANDLE_X)
	{
		shape = &xDirection;
	}
	else if (handle == MANIPULATOR_HANDLE_Y) 
	{
		shape = &yDirection;
	}
	else if (handle == MANIPULATOR_HANDLE_Z) 
	{
		shape = &zDirection;
	}
	else
	{
		assert(0);
	}

	faceList = shape->cone.Position();
	faceIndex = shape->cone.Index();
}

void MoveManipulator::GetEdgeList(vector<vec3>& edgeList, vector<int>& edgeIndex, MANIPULATOR_HANDLE handle)
{
	ShapeData* shape = nullptr;
	if (handle == MANIPULATOR_HANDLE_X)
	{
		shape = &xDirection;
	}
	else if (handle == MANIPULATOR_HANDLE_Y)
	{
		shape = &yDirection;
	}
	else if (handle == MANIPULATOR_HANDLE_Z)
	{
		shape = &zDirection;
	}
	else
	{
		assert(0);
	}

	edgeList = shape->position;
	edgeIndex.push_back(0); edgeIndex.push_back(1);

}
}
}