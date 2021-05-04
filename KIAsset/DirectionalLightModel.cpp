namespace KI
{
namespace Asset
{
DirectionalLightModel::DirectionalLightModel()
{
	Build();
}

DirectionalLightModel::~DirectionalLightModel()
{
}

void DirectionalLightModel::Build()
{
	Cone cone;
	cone.Build(ConeArgs(1, 1, 4));
	mat4x4 xMatrix = mat4x4(1);
	xMatrix = glm::rotate(xMatrix, pi<float>() / 2, vec3(0, 0, 1));
	xMatrix = glm::translate(xMatrix, vec3(0, -1.1, 0));
	cone.Multi(xMatrix);

	Cube cube((int)cone.Position().size());
	cube.Build(CubeArgs(vec3(-0.5), vec3(0.5)));
	
	m_position.insert(m_position.end(), cone.Position().begin(), cone.Position().end());
	m_position.insert(m_position.end(), cube.Position().begin(), cube.Position().end());

	m_index.insert(m_index.end(), cone.Index().begin(), cone.Index().end());
	m_index.insert(m_index.end(), cube.Index().begin(), cube.Index().end());

	m_drawType = GL_TRIANGLES;
}


}
}