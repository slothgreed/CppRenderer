namespace KI
{

ModelGenerator::ModelGenerator()
{
}

ModelGenerator::~ModelGenerator()
{
}

void ModelGenerator::Axis(VertexBuffer* vertexBuffer)
{
	if (vertexBuffer == NULL)
	{
		assert(0);
		return;
	}

	std::vector<vec3> position;
	position.reserve(6);
	position.push_back(vec3(-0.5, 0.0, 0.0));
	position.push_back(vec3(0.5, 0.0, 0.0));
	position.push_back(vec3(0.0, -0.5, 0.0));
	position.push_back(vec3(0.0, 0.5, 0.0));
	position.push_back(vec3(0.0, 0.0, -0.5));
	position.push_back(vec3(0.0, 0.0, 0.5));

	std::vector<vec3> color;
	color.reserve(6);
	color.push_back(vec3(1.0, 0.0, 0.0));
	color.push_back(vec3(1.0, 0.0, 0.0));
	color.push_back(vec3(0.0, 1.0, 0.0));
	color.push_back(vec3(0.0, 1.0, 0.0));
	color.push_back(vec3(0.0, 0.0, 1.0));
	color.push_back(vec3(0.0, 0.0, 1.0));

	vertexBuffer->Generate(VERTEX_LAYOUT_PC);
	vertexBuffer->SetPosition(GL_LINES, position);
	vertexBuffer->SetColor(color);
}
}