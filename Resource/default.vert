#include "common\common.h"
#include "common\struct.h"
#include "common\default.vbo"

#if defined(OUT_NORMAL) || defined(OUT_COLOR) || defined(OUT_TEXCOORD) || defined(OUT_INSTANCE)
out Data{
#ifdef OUT_NORMAL
out vec3 normal;
#endif

#ifdef OUT_COLOR
out vec4 color;
#endif
#ifdef OUT_TEXCOORD
out vec2 texcoord;
#endif
#ifdef OUT_INSTANCE
out vec4 instanceMatrix0;
out vec4 instanceMatrix1;
out vec4 instanceMatrix2;
out vec4 instanceMatrix3;
#endif

}OutData;
#endif

void main()
{
	gl_Position = OutputPosition();

#if defined(OUT_NORMAL)
	OutData.normal = OutputNormal();
#endif

#if defined(OUT_COLOR)
	OutData.color = OutputColor();
#endif

#if defined(OUT_TEXCOORD)
	OutData.texcoord = OutputTexcoord();
#endif

#if defined(OUT_INSTANCE)
	OutData.instanceMatrix0 = OutputInstance0();
	OutData.instanceMatrix1 = OutputInstance1();
	OutData.instanceMatrix2 = OutputInstance2();
	OutData.instanceMatrix3 = OutputInstance3();
#endif
}