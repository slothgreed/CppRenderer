#ifndef SHADER_STRUCT_TXT
#define SHADER_STRUCT_TXT

layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;

layout (std140) uniform LightData
{
	vec4 Direction;
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
}light;


layout (std140) uniform MaterialData
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	float Shinning;
}material;

#endif