#ifndef SHADER_COMMON_H
#define SHADER_COMMON_H

vec3 NotDefineNormal()
{
	return vec4(0,0,0);
}

vec4 NotDefineColor()
{
	return vec4(1,1,0,1);
}

vec2 NotDefineTexCoord()
{
	return vec2(0,0);
}

#define SHADER_COMMON_H
