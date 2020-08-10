#include "common\struct.h"

out vec4 outputColor;

void main()
{
	outputColor = vec4(float(model.objectId),float(gl_PrimitiveID + 1),0.0,1.0);
	outputColor = vec4(1.0, 1.0, 0.0, 1.0);
}