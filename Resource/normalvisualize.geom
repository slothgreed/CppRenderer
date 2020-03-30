
layout(points) in;
layout(line_strip, max_vertices = 2) out;

layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;



in Inputs
{
	vec4 o_color;
}vIn[1];

in vec3 o_normal[];
out vec4 o_color;

void main()
{
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * gl_in[0].gl_Position;
	o_color = vec4(1);
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + o_normal[0],1.0);
	o_color = vec4(1);
	EmitVertex();
	EndPrimitive();
}