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
	position.push_back(vec3(0.5, 2, 0));
	position.push_back(vec3(1.5, 0, 0));
	position.push_back(vec3(2, 2, 0));

	pVertexBuffer->SetPosition(GL_PATCHES, position);
}
}
}