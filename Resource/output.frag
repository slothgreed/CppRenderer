
out vec4 outputColor;

uniform sampler2D uTexture0;

in Data{
	vec2 texcoord;
}OutData;
void main()
{
	outputColor = texture2D(uTexture0,OutData.texcoord);
}