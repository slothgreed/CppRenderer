namespace KI
{

namespace Gfx
{

PRIM_TYPE GLTypeUtility::PrimType(GLuint value)
{
	if (value == PRIM_TYPE_POINTS) {
		return PRIM_TYPE_POINTS;
	}
	else if (value == PRIM_TYPE_LINES) {
		return PRIM_TYPE_LINES;
	}
	else if (value == PRIM_TYPE_LINE_STRIP) {
		return PRIM_TYPE_LINE_STRIP;
	}
	else if (value == PRIM_TYPE_POINTS) {
		return PRIM_TYPE_POINTS;
	}
	else if (value == PRIM_TYPE_LINE_LOOP) {
		return PRIM_TYPE_LINE_LOOP;
	}
	else if (value == PRIM_TYPE_TRIANGLES) {
		return PRIM_TYPE_TRIANGLES;
	}
	else if (value == PRIM_TYPE_TRIANGLE_STRIP) {
		return PRIM_TYPE_TRIANGLE_STRIP;
	}
	else if (value == PRIM_TYPE_TRIANGLE_FAN) {
		return PRIM_TYPE_TRIANGLE_FAN;
	}
	else if (value == PRIM_TYPE_PATCHES) {
		return PRIM_TYPE_PATCHES;
	}
	else
	{
		assert(0);
		return PRIM_TYPE_POINTS;
	}
}

}
}