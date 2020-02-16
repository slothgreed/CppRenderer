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
	position.push_back(vec3(0, 0, 0));
	position.push_back(vec3(1, 0, 0)); 
	Cone xCone;
	xCone.Build(1, 1, 10);
	mat4x4 xMatrix = glm::rotate(mat4x4(), pi<float>(), vec3(0, 0, 1));
	xMatrix = glm::translate(xMatrix, vec3(0, 0, 1));
	xCone.Multi(xMatrix);

	// y axis
	position.push_back(vec3(0, 0, 0));
	position.push_back(vec3(0, 1, 0));
	Cone yCone;
	yCone.Build(1, 1, 10);
	mat4x4 yMatrix = glm::translate(mat4x4(), vec3(0, 1, 0));
	yCone.Multi(yMatrix);

	// z axis
	position.push_back(vec3(0, 0, 0));
	position.push_back(vec3(0, 0, 1));
	Cone zCone;
	zCone.Build(1, 1, 10);
	mat4x4 zMatrix = glm::rotate(mat4x4(), pi<float>(), vec3(1, 0, 0));
	zMatrix = glm::rotate(zMatrix, pi<float>(), vec3(1, 0, 0));
	zCone.Multi(zMatrix);
}

void MoveManipulator::GetVertexList(vector<Vertex>& vertex)
{

}

void MoveManipulator::GetEdgeIndexList(vector<int>& index)
{

}

void MoveManipulator::GetFaceIndexList(vector<int> & index)
{

}

}