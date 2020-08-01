namespace KI
{
namespace Asset
{
ScaleManipulator::ScaleManipulator()
{
}

ScaleManipulator::~ScaleManipulator()
{
}

void ScaleManipulator::Build()
{
	vector<vec3> position;
	// x axis
	mat4x4 xMatrix = mat4x4(1);
	xDirection.cube.Build(CubeArgs(vec3(-0.5), vec3(0.5)));
	xMatrix = glm::translate(xMatrix, vec3(1, 0, 0));
	xMatrix = glm::scale(xMatrix, vec3(0.1f));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.cube.Multi(xMatrix);

	xDirection.cylinder.SetIndexOffset(xDirection.cube.Position().size());
	xDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	xMatrix = mat4x4(1);
	xMatrix = glm::scale(xMatrix, vec3(0.025f));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.cylinder.Multi(xMatrix);

	// y axis
	yDirection.cube.Build(CubeArgs(vec3(-0.5), vec3(0.5)));
	mat4x4 yMatrix = mat4x4(1);
	yMatrix = glm::translate(yMatrix, vec3(0, 1, 0));
	yMatrix = glm::scale(yMatrix, vec3(0.1f));
	yDirection.cube.Multi(yMatrix);

	yDirection.cylinder.SetIndexOffset(yDirection.cube.Position().size());
	yDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	yMatrix = mat4x4(1);
	yMatrix = glm::scale(yMatrix, vec3(0.025f));
	yDirection.cylinder.Multi(yMatrix);


	// z axis
	zDirection.cube.Build(CubeArgs(vec3(-0.5), vec3(0.5)));
	mat4x4 zMatrix = mat4x4(1);
	zMatrix = glm::translate(zMatrix, vec3(0, 0, 1));
	zMatrix = glm::scale(zMatrix, vec3(0.1f));
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.cube.Multi(zMatrix);

	zDirection.cylinder.SetIndexOffset(zDirection.cube.Position().size());
	zDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	zMatrix = mat4x4(1);
	zMatrix = glm::scale(zMatrix, vec3(0.025f));
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.cylinder.Multi(zMatrix);

}


void ScaleManipulator::GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle)
{
	if (handle == MANIPULATOR_HANDLE_X)
	{
		faceList = xDirection.cube.Position();
		faceList.insert(faceList.end(),
			xDirection.cylinder.Position().begin(),
			xDirection.cylinder.Position().end());
		faceIndex = xDirection.cube.Index();
		faceIndex.insert(faceIndex.end(),
			xDirection.cylinder.Index().begin(),
			xDirection.cylinder.Index().end());

	}
	else if (handle == MANIPULATOR_HANDLE_Y) 
	{
		faceList = yDirection.cube.Position();
		faceList.insert(faceList.end(),
			yDirection.cylinder.Position().begin(),
			yDirection.cylinder.Position().end());
		faceIndex = yDirection.cube.Index();
		faceIndex.insert(faceIndex.end(),
			yDirection.cylinder.Index().begin(),
			yDirection.cylinder.Index().end());
	}
	else if (handle == MANIPULATOR_HANDLE_Z) 
	{
		faceList = zDirection.cube.Position();
		faceList.insert(faceList.end(),
			zDirection.cylinder.Position().begin(),
			zDirection.cylinder.Position().end());
		faceIndex = zDirection.cube.Index();
		faceIndex.insert(faceIndex.end(),
			zDirection.cylinder.Index().begin(),
			zDirection.cylinder.Index().end());
	}
	else
	{
		assert(0);
	}
}
}
}