namespace KI
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
	mat4x4 identifier = mat4x4(1);
	//mat4x4 xMatrix = glm::rotate(mat4x4(1), pi<float>(), vec3(0, 0, 1));
	//xMatrix = glm::translate(xMatrix, vec3(0, 0, 1));
	//xDirection.cone.Multi(xMatrix);

	// y axis
	yDirection.position.push_back(vec3(0, 0, 0));
	yDirection.position.push_back(vec3(0, 1, 0));
	yDirection.cone.Build(1, 1, 10);
	mat4x4 yMatrix = glm::translate(mat4x4(1), vec3(0, 1, 0));
	yDirection.cone.Multi(yMatrix);

	// z axis
	zDirection.position.push_back(vec3(0, 0, 0));
	zDirection.position.push_back(vec3(0, 0, 1));
	yDirection.cone.Build(1, 1, 10);
	mat4x4 zMatrix = glm::rotate(mat4x4(1), pi<float>(), vec3(1, 0, 0));
	zMatrix = glm::rotate(zMatrix, pi<float>(), vec3(1, 0, 0));
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