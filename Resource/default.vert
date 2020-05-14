#include "common/common.h"
#include "common/struct.txt"
#include "common/default.vbo"

out Data{

#if defined(OUT_NORMAL)
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

<<<Embedded Ext Code>>>

void main()
{
	gl_Position = OutputPosition();

#if defined(OUT_NORMAL) && defined(OUT_NORMAL_EXT)
	OutData.normal = OutputNormalExt();
#elif defined(OUT_NORMAL)
	OutData.normal = OutputNormal();
#endif

#if defined(OUT_COLOR) && defined(OUT_COLOR_EXT)
	OutData.color = OutputColorExt();
#elif defined(OUT_COLOR)
	OutData.color = OutputColor();
#endif

#if defined(OUT_TEXCOORD) && defined(OUT_TEXCOORD_EXT)
	OutData.texcoord = OutputTexcoordExt();
#elif defined(OUT_TEXCOORD)
	OutData.texcoord = OutputTexcoord();
#endif

#if defined(OUT_INSTANCE) && defined(OUT_INSTANCE_EXT)
	OutData.instance0 = OutputInstanceExt0();
	OutData.instance1 = OutputInstanceExt1();
	OutData.instance2 = OutputInstanceExt2();
	OutData.instance3 = OutputInstanceExt3();
#elif defined(OUT_INSTANCE)
	OutData.instance0 = OutputInstance0();
	OutData.instance1 = OutputInstance1();
	OutData.instance2 = OutputInstance2();
	OutData.instance3 = OutputInstance3();
#endif
}