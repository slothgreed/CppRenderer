#include "Axis.h"
namespace KI
{
namespace Asset
{

Axis::Axis(const AxisArgs& args)
{
	Build(args);
}

Axis::~Axis()
{
}

void Axis::Build(const AxisArgs& args)
{
	m_position.reserve(6);
	m_position.push_back(vec3(args.min.x, 0.0, 0.0));
	m_position.push_back(vec3(args.max.x, 0.0, 0.0));
	m_position.push_back(vec3(0.0, args.min.y, 0.0));
	m_position.push_back(vec3(0.0, args.max.y, 0.0));
	m_position.push_back(vec3(0.0, 0.0, args.min.z));
	m_position.push_back(vec3(0.0, 0.0, args.max.z));

	m_color.reserve(6);
	m_color.push_back(vec3(1.0, 0.0, 0.0));
	m_color.push_back(vec3(1.0, 0.0, 0.0));
	m_color.push_back(vec3(0.0, 1.0, 0.0));
	m_color.push_back(vec3(0.0, 1.0, 0.0));
	m_color.push_back(vec3(0.0, 0.0, 1.0));
	m_color.push_back(vec3(0.0, 0.0, 1.0));

	m_drawType = GL_LINES;
}

}
}