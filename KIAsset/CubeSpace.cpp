#include "Axis.h"
namespace KI
{
namespace Asset
{

CubeSpace::CubeSpace(const CubeSpaceArgs& args)
{
	Build(args);
}

CubeSpace::~CubeSpace()
{
}

void CubeSpace::Build(const CubeSpaceArgs& args)
{
	m_position.reserve(24);
	m_texcoord.reserve(24);

	vec3 min = args.size.Min();
	vec3 max = args.size.Max();
	float width = 1;
	float height = 1;
	float widthCell = width / 4;
	float heightCell = height / 3;
	// back
	m_position.push_back(vec3(min.x, min.y, max.z));
	m_position.push_back(vec3(min.x, max.y, max.z));
	m_position.push_back(vec3(max.x, max.y, max.z));
	m_position.push_back(vec3(max.x, min.y, max.z));
	m_texcoord.push_back(vec2(widthCell, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell, heightCell));
	m_texcoord.push_back(vec2(0, heightCell));
	m_texcoord.push_back(vec2(0, heightCell * 2));

	// right
	m_position.push_back(vec3(min.x, min.y, min.z));
	m_position.push_back(vec3(min.x, max.y, min.z));
	m_position.push_back(vec3(min.x, max.y, max.z));
	m_position.push_back(vec3(min.x, min.y, max.z));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell));
	m_texcoord.push_back(vec2(widthCell, heightCell));
	m_texcoord.push_back(vec2(widthCell, heightCell * 2));

	// left
	m_position.push_back(vec3(max.x, min.y, min.z));
	m_position.push_back(vec3(max.x, min.y, max.z));
	m_position.push_back(vec3(max.x, max.y, max.z));
	m_position.push_back(vec3(max.x, max.y, min.z));
	m_texcoord.push_back(vec2(widthCell * 3, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell * 4, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell * 4, heightCell));
	m_texcoord.push_back(vec2(widthCell * 3, heightCell));

	// top
	m_position.push_back(vec3(min.x, max.y, min.z));
	m_position.push_back(vec3(max.x, max.y, min.z));
	m_position.push_back(vec3(max.x, max.y, max.z));
	m_position.push_back(vec3(min.x, max.y, max.z));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell));
	m_texcoord.push_back(vec2(widthCell * 2, 0));
	m_texcoord.push_back(vec2(widthCell, 0));
	m_texcoord.push_back(vec2(widthCell, heightCell));

	// bottom
	m_position.push_back(vec3(min.x, min.y, min.z));
	m_position.push_back(vec3(min.x, min.y, max.z));
	m_position.push_back(vec3(max.x, min.y, max.z));
	m_position.push_back(vec3(max.x, min.y, min.z));
	m_texcoord.push_back(vec2(widthCell, heightCell * 3));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell * 3));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell, heightCell * 2));

	// front
	m_position.push_back(vec3(min.x, min.y, min.z));
	m_position.push_back(vec3(max.x, min.y, min.z));
	m_position.push_back(vec3(max.x, max.y, min.z));
	m_position.push_back(vec3(min.x, max.y, min.z));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell * 3, heightCell * 2));
	m_texcoord.push_back(vec2(widthCell * 3, heightCell));
	m_texcoord.push_back(vec2(widthCell * 2, heightCell));

	int offset = 0;
	m_index.reserve(36);
	for (int i = 0; i < 6; i++)
	{
		m_index.push_back(0 + offset); m_index.push_back(1 + offset); m_index.push_back(2 + offset);
		m_index.push_back(0 + offset); m_index.push_back(2 + offset); m_index.push_back(3 + offset);
		offset += 4;
	}

	m_drawType = GL_TRIANGLES;
}

}
}