namespace KI
{
namespace Asset
{
ModelGenerator::ModelGenerator()
{
}

ModelGenerator::~ModelGenerator()
{
}

void ModelGenerator::Plane(RenderData* pRenderData, VERTEX_LAYOUT layout)
{
	if (pRenderData == NULL)
	{
		assert(0);
		return;
	}

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();

	vector<vec3> position;
	position.reserve(4);
	position.push_back(vec3(-1, -1, 0));
	position.push_back(vec3(1, -1, 0));
	position.push_back(vec3(-1, 1, 0));
	position.push_back(vec3(1, 1, 0));
	pVertexBuffer->SetPosition(position);

	vector<vec2> texcoord;
	texcoord.reserve(4);
	if (layout & VERTEX_LAYOUT_TEXCOORD)
	{
		texcoord.push_back(vec2(0, 0));
		texcoord.push_back(vec2(1, 0));
		texcoord.push_back(vec2(0, 1));
		texcoord.push_back(vec2(1, 1));
		pVertexBuffer->SetTexcoord(texcoord);
	}

	vector<vec3> color;
	color.reserve(4);
	if (layout & VERTEX_LAYOUT_COLOR)
	{
		color.push_back(vec3(0, 0, 0));
		color.push_back(vec3(1, 0, 0));
		color.push_back(vec3(0, 1, 0));
		color.push_back(vec3(1, 1, 0));
		pVertexBuffer->SetColor(color);

	}

	pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLE_STRIP, pVertexBuffer);

}
}
}