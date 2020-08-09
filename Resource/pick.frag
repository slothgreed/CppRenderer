
out vec3 outputColor;

uniform sampler2D uTexture0;

void main()
{
	outputColor = vec3(float(model.objectId),float(gl_PrimitiveID + 1),1.0);
}