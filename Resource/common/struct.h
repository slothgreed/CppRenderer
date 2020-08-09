#ifndef SHADER_STRUCT_TXT
#define SHADER_STRUCT_TXT

layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;

layout (std140) uniform LightData
{
	vec4 Position;
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;
	float SpotCutoff;
	float SpotExponent;
	vec4 SpotDirection;
}light;

layout (std140) uniform ModelData
{
	mat4 ModelMatrix;
	mat4 NormalMatrix;
	int reserve1;
}model;

layout (std140) uniform MaterialData
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	float Shinning;
}material;


#endif