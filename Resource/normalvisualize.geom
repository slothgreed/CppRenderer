#include "common\common.h"
#include "common\struct.h"
layout(points) in;
layout(line_strip, max_vertices = 2) out;


uniform float uLength;
in Data
{
	vec3 normal;
}InData[1];

void main()
{
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * gl_in[0].gl_Position;
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + InData[0].normal*uLength,1.0);
	EmitVertex();
	EndPrimitive();
}