#ifndef SHADER_COMMON_H
#define SHADER_COMMON_H

vec3 NotDefineNormal()
{
	return vec3(0,0,0);
}

vec4 NotDefineColor()
{
	return vec4(1,1,0,1);
}

vec2 NotDefineTexcoord()
{
	return vec2(0,0);
}

vec4 WorldPosition(mat4 viewMatrix, vec3 position)
{
	vec4 pos = viewMatrix * vec4(position,1.0);
	return pos /= pos.w;
}
#endif
