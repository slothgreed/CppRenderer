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
	xDirection.torus.Build(TorusArgs(0.09f, 1, 32, 32));
	xMatrix = glm::rotate(xMatrix, -pi<float>() / 2, vec3(0, 0, 1));
	xDirection.torus.Multi(xMatrix);

	// y axis
	yDirection.torus.Build(TorusArgs(0.09f, 1, 32, 32));
	mat4x4 yMatrix = mat4x4(1);
	yDirection.torus.Multi(yMatrix);

	// z axis
	zDirection.torus.Build(TorusArgs(0.09f, 1, 32, 32));
	mat4x4 zMatrix = mat4x4(1);
	zMatrix = glm::rotate(zMatrix, pi<float>() / 2, vec3(1, 0, 0));
	zDirection.torus.Multi(zMatrix);
}


void RotateManipulator::GetFaceList(vector<vec3>& faceList, vector<int>& faceIndex, MANIPULATOR_HANDLE handle)
{
	if (handle == MANIPULATOR_HANDLE_X)
	{
		faceList = xDirection.torus.Position();
		faceIndex = xDirection.torus.Index();
	}
	else if (handle == MANIPULATOR_HANDLE_Y) 
	{
		faceList = yDirection.torus.Position();
		faceIndex = yDirection.torus.Index();
	}
	else if (handle == MANIPULATOR_HANDLE_Z) 
	{
		faceList = zDirection.torus.Position();
		faceIndex = zDirection.torus.Index();
	}
	else
	{
		assert(0);
	}
}
}
}