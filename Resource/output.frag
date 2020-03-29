
out vec4 outputColor;

in vec2 o_texcoord;
uniform sampler2D uTexture0;

void main()
{
	outputColor = texture2D(uTexture0,o_texcoord);
}