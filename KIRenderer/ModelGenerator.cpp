namespace KI
{
namespace Renderer
{
ModelGenerator::ModelGenerator()
{
}

ModelGenerator::~ModelGenerator()
{
}

void ModelGenerator::Axis(DefaultVertexBuffer* vertexBuffer)
{
	if (vertexBuffer == NULL)
	{
		assert(0);
		return;
	}

	std::vector<vec3> position;
	position.reserve(6);
	position.push_back(vec3(-1, 0.0, 0.0));
	position.push_back(vec3(1, 0.0, 0.0));
	position.push_back(vec3(0.0, -1, 0.0));
	position.push_back(vec3(0.0, 1, 0.0));
	position.push_back(vec3(0.0, 0.0, -1));
	position.push_back(vec3(0.0, 0.0, 1));

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

void ModelGenerator::RenderPlane(DefaultVertexBuffer* vertexBuffer)
{
	if (vertexBuffer == NULL)
	{
		assert(0);
		return;
	}

	vector<vec3> position;
	position.reserve(4);
	position.push_back(vec3(-1, -1, 0));
	position.push_back(vec3(1, -1, 0));
	position.push_back(vec3(-1, 1, 0));
	position.push_back(vec3(1, 1, 0));

	vector<vec2> texcoord;
	texcoord.push_back(vec2(0, 0));
	texcoord.push_back(vec2(1, 0));
	texcoord.push_back(vec2(0, 1));
	texcoord.push_back(vec2(1, 1));

	vertexBuffer->Generate(VERTEX_LAYOUT_PT);
	vertexBuffer->SetPosition(GL_TRIANGLE_STRIP, position);
	vertexBuffer->SetTexcoord(texcoord);
}
}
}