
layout (std140) uniform Scene
{
	mat4 Projection;
	mat4 ViewMatrix;
	vec4 color;
};


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec4 v_color;
void main()
{
	mat4 vp = Projection * ViewMatrix;
	gl_Position = vp * vec4(position,1.0);
	v_color = vec4(normal,1.0);
}