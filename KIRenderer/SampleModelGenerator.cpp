namespace KI
{
namespace Renderer
{
SampleModelGenerator::SampleModelGenerator()
{
}

SampleModelGenerator::~SampleModelGenerator()
{
}

void SampleModelGenerator::BezierLine(DefaultVertexBuffer* pVertexBuffer)
{
	vector<vec3> position;

	position.push_back(vec3(0, 0, 0));
	position.push_back(vec3(0, 1, 0));
	position.push_back(vec3(1, 0, 0));
	position.push_back(vec3(1, 1, 0));

	pVertexBuffer->SetPosition(GL_PATCHES, position);
}
}
}