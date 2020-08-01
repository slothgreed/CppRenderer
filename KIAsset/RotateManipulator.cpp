namespace KI
{
namespace Asset
{
RotateManipulator::RotateManipulator()
{
}

RotateManipulator::~RotateManipulator()
{
}

void RotateManipulator::Build()
{
	vector<vec3> position;
	// x axis
	mat4x4 xMatrix = mat4x4(1);
	xDirection.cone.Build(ConeArgs(1, 2, 10));
	xMatrix = glm::translate(xMatrix, vec3(1, 0, 0));
	xMatrix = glm::scale(xMatrix, vec3(0.1f));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.cone.Multi(xMatrix);

	xDirection.cylinder.SetIndexOffset(xDirection.cone.Position().size());
	xDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	xMatrix = mat4x4(1);
	xMatrix = glm::scale(xMatrix, vec3(0.025f));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.cylinder.Multi(xMatrix);

	// y axis
	yDirection.cone.Build(ConeArgs(1, 2, 10));
	mat4x4 yMatrix = mat4x4(1);
	yMatrix = glm::translate(yMatrix, vec3(0, 1, 0));
	yMatrix = glm::scale(yMatrix, vec3(0.1f));
	yDirection.cone.Multi(yMatrix);

	yDirection.cylinder.SetIndexOffset(yDirection.cone.Position().size());
	yDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	yMatrix = mat4x4(1);
	yMatrix = glm::scale(yMatrix, vec3(0.025f));
	yDirection.cylinder.Multi(yMatrix);


	// z axis
	zDirection.cone.Build(ConeArgs(1, 2, 10));
	mat4x4 zMatrix = mat4x4(1);
	zMatrix = glm::translate(zMatrix, vec3(0, 0, 1));
	zMatrix = glm::scale(zMatrix, vec3(0.1f));
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.cone.Multi(zMatrix);

	zDirection.cylinder.SetIndexOffset(zDirection.cone.Position().size());
	zDirection.cylinder.Build(CylinderArgs(1, 1, 40, 10));
	zMatrix = mat4x4(1);
	zMatrix = glm::scale(zMatrix, vec3(0.025f));
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.cylinder.Multi(zMatrix);

}


void RotateManipulator::GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle)
{
	if (handle == MANIPULATOR_HANDLE_X)
	{
		faceList = xDirection.cone.Position();
		faceList.insert(faceList.end(),
			xDirection.cylinder.Position().begin(),
			xDirection.cylinder.Position().end());
		faceIndex = xDirection.cone.Index();
		faceIndex.insert(faceIndex.end(),
			xDirection.cylinder.Index().begin(),
			xDirection.cylinder.Index().end());

	}
	else if (handle == MANIPULATOR_HANDLE_Y) 
	{
		faceList = yDirection.cone.Position();
		faceList.insert(faceList.end(),
			yDirection.cylinder.Position().begin(),
			yDirection.cylinder.Position().end());
		faceIndex = yDirection.cone.Index();
		faceIndex.insert(faceIndex.end(),
			yDirection.cylinder.Index().begin(),
			yDirection.cylinder.Index().end());
	}
	else if (handle == MANIPULATOR_HANDLE_Z) 
	{
		faceList = zDirection.cone.Position();
		faceList.insert(faceList.end(),
			zDirection.cylinder.Position().begin(),
			zDirection.cylinder.Position().end());
		faceIndex = zDirection.cone.Index();
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