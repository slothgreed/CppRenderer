
out vec4 outputColor;

in vec2 v_texcoord;
uniform sampler2D uTexture0;

void main()
{
	outputColor = texture2D(uTexture0,v_texcoord);
}