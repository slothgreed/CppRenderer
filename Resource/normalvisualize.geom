
layout(points) in;
layout(points, max_vertices = 1) out;

/*
layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;
*/


in Inputs
{
	vec3 o_normal;
	vec4 o_color;
}vIn[1];

out vec4 o_color;

void main()
{
/*
	mat4 vp = scene.Projection * scene.ViewMatrix;

	gl_Position = vp * gl_in[0].gl_Position;
	o_color = vIn[0].o_color;
	EmitVertex();
	
	gl_Position = vp * (gl_in[0].gl_Position + vec4(vIn[0].o_normal,1.0));
	o_color = vIn[0].o_color;
	EmitVertex();
	EndPrimitive();
*/
	//mat4 vp = scene.Projection * scene.ViewMatrix;

	gl_Position = gl_in[0].gl_Position;
	o_color = vIn[0].o_color;
	EmitVertex();
	
	/*gl_Position = (gl_in[0].gl_Position + vec4(vIn[0].o_normal,1.0));
	o_color = vIn[0].o_color;
	EmitVertex();*/
	EndPrimitive();
}