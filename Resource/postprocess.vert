
layout(location = 0) in vec3 a_position;
layout(location = 3) in vec2 a_texcoord;

out Data{
	vec2 texcoord;
}OutData;

void main()
{
	gl_Position = vec4(a_position,1.0);
	OutData.texcoord = a_texcoord;
}