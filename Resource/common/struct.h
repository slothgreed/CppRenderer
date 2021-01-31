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
	vec4 SpotDirection;
	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;
	float SpotCutoff;
	float SpotExponent;
}light;

layout (std140) uniform ModelData
{
	mat4 ModelViewMatrix;
	mat4 ModelMatrix;
	mat4 NormalMatrix;
	int objectId;
}model;

layout (std140) uniform MaterialData
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	float Shinning;
}material;


#endif