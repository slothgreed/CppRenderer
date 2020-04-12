
out vec4 outputColor;

uniform sampler2D uTexture0;

in Data{
	vec2 texcoord;
}OutData;
void main()
{
	vec4 color = texture2D(uTexture0,OutData.texcoord);
	float value = 0.299*color.x + 0.587*color.y + 0.114*color.z;

	outputColor = vec4(value,value,value,1);
}