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

void ModelGenerator::Axis(DefaultVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer == NULL)
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

	pVertexBuffer->SetPosition(GL_LINES, position);
	pVertexBuffer->SetColor(color);
}

void ModelGenerator::RenderPlane(DefaultVertexBuffer* pVertexBuffer)
{
	if (pVertexBuffer == NULL)
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

	pVertexBuffer->SetPosition(GL_TRIANGLE_STRIP, position);
	pVertexBuffer->SetTexcoord(texcoord);
}

void ModelGenerator::CubeSpace(const BDB& size, DefaultVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer)
{
	vector<vec3> position;
	position.reserve(24);
	vector<vec2> texcoord;
	texcoord.reserve(24);

	vec3 min = size.Min();
	vec3 max = size.Max();
	float width = 1;
	float height = 1;
	float widthCell = width / 4;
	float heightCell = height / 3;
	// back
	position.push_back(vec3(min.x, min.y, max.z));
	position.push_back(vec3(min.x, max.y, max.z));
	position.push_back(vec3(max.x, max.y, max.z));
	position.push_back(vec3(max.x, min.y, max.z));
	texcoord.push_back(vec2(widthCell, heightCell * 2));
	texcoord.push_back(vec2(widthCell, heightCell));
	texcoord.push_back(vec2(0, heightCell));
	texcoord.push_back(vec2(0, heightCell * 2));

	// right
	position.push_back(vec3(min.x, min.y, min.z));
	position.push_back(vec3(min.x, max.y, min.z));
	position.push_back(vec3(min.x, max.y, max.z));
	position.push_back(vec3(min.x, min.y, max.z));
	texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	texcoord.push_back(vec2(widthCell * 2, heightCell));
	texcoord.push_back(vec2(widthCell, heightCell));
	texcoord.push_back(vec2(widthCell, heightCell * 2));

	// left
	position.push_back(vec3(max.x, min.y, min.z));
	position.push_back(vec3(max.x, min.y, max.z));
	position.push_back(vec3(max.x, max.y, max.z));
	position.push_back(vec3(max.x, max.y, min.z));
	texcoord.push_back(vec2(widthCell * 3, heightCell * 2));
	texcoord.push_back(vec2(widthCell * 4, heightCell * 2));
	texcoord.push_back(vec2(widthCell * 4, heightCell));
	texcoord.push_back(vec2(widthCell * 3, heightCell));

	// top
	position.push_back(vec3(min.x, max.y, min.z));
	position.push_back(vec3(max.x, max.y, min.z));
	position.push_back(vec3(max.x, max.y, max.z));
	position.push_back(vec3(min.x, max.y, max.z));
	texcoord.push_back(vec2(widthCell * 2, heightCell));
	texcoord.push_back(vec2(widthCell * 2, 0));
	texcoord.push_back(vec2(widthCell, 0));
	texcoord.push_back(vec2(widthCell, heightCell));

	// bottom
	position.push_back(vec3(min.x, min.y, min.z));
	position.push_back(vec3(min.x, min.y, max.z));
	position.push_back(vec3(max.x, min.y, max.z));
	position.push_back(vec3(max.x, min.y, min.z));
	texcoord.push_back(vec2(widthCell, heightCell * 3));
	texcoord.push_back(vec2(widthCell * 2, heightCell * 3));
	texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	texcoord.push_back(vec2(widthCell, heightCell * 2));

	// front
	position.push_back(vec3(min.x, min.y, min.z));
	position.push_back(vec3(max.x, min.y, min.z));
	position.push_back(vec3(max.x, max.y, min.z));
	position.push_back(vec3(min.x, max.y, min.z));
	texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	texcoord.push_back(vec2(widthCell * 3, heightCell * 2));
	texcoord.push_back(vec2(widthCell * 3, heightCell));
	texcoord.push_back(vec2(widthCell * 2, heightCell));

	pVertexBuffer->SetPosition(GL_TRIANGLES, position);
	pVertexBuffer->SetTexcoord(texcoord);

	vector<int> index;
	int offset = 0;
	index.reserve(36);
	for (int i = 0; i < 6; i++)
	{
		index.push_back(0 + offset); index.push_back(1 + offset); index.push_back(2 + offset);
		index.push_back(0 + offset); index.push_back(2 + offset); index.push_back(3 + offset);
		offset += 4;
	}

	pIndexBuffer->Set(GL_TRIANGLES, index);
}
}
}