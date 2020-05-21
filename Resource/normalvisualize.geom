
layout(points) in;
layout(line_strip, max_vertices = 2) out;

layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;


uniform float uLength;
in Data
{
	vec3 normal;
}InData[1];


out Data
{
	vec4 color;
}OutData;
out vec4 o_color;

void main()
{
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * gl_in[0].gl_Position;
	OutData.color = vec4(1);
	EmitVertex();
	
	gl_Position = vp * vec4(gl_in[0].gl_Position.xyz + InData[0].normal*uLength,1.0);
	OutData.color = vec4(1);
	EmitVertex();
	EndPrimitive();
}