#include "common\common.h"
#include "common\struct.h"

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;

out Data{
out vec3 normal;
out vec3 tangent;
}OutData;

void main()
{
	gl_Position = vec4(a_position,1.0);
	OutData.normal = a_normal;
	OutData.tangent = a_tangent;

}