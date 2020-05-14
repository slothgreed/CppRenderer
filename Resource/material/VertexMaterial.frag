
out vec4 outputColor;

in Data{
	in vec4 color;
}InData;

void main()
{
	outputColor = InData.color;
}