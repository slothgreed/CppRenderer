
layout(triangles) in;
layout(lines, max_vertices = 2) out;

in Inputs
{
	vec3 o_normal;
}in[3];

out vec3 o_color;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	o_color = in[0].o_normal;
	EmitVertex();
	
	gl_Position = gl_in[1].gl_Position + o_normal;
	o_color = in[0].o_color;
}