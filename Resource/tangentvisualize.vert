#include "common\common.h"
#include "common\struct.h"
#include "common\default.vbo"

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;

out Data{
out vec3 normal;
out vec3 tangent;
}OutData;

void main()
{
	gl_Position = WorldPosition(scene.ViewMatrix, a_position);

	OutData.normal = a_normal;
	OutData.tangent = a_tangent;

}