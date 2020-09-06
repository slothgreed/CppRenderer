#include "common\struct.h"

out vec4 outputColor;

void main()
{
	outputColor = vec4((model.objectId),(gl_PrimitiveID + 1),0.0,1.0);
}