
out vec4 outputColor;

in vec2 v_texcoord;
uniform sampler2D uTexture0;

void main()
{
	vec4 color = texture2D(uTexture0,v_texcoord);
	float value = 0.299*color.x + 0.587*color.y + 0.114*color.z;

	outputColor = vec4(value,value,value,1);
}