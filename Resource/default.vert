
layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;

layout(location = 0) in vec3 a_position;

#ifdef IN_NORMAL
layout(location = 1) in vec3 a_normal;
#endif

#ifdef IN_COLOR
layout(location = 2) in vec3 a_color;
#endif

#ifdef IN_TEXCOORD
layout(location = 3) in vec2 a_texcoord;
#endif


#ifdef IN_INSTANCE
layout(location = 4) in vec4 a_instanceMatrix0;
layout(location = 5) in vec4 a_instanceMatrix1;
layout(location = 6) in vec4 a_instanceMatrix2;
layout(location = 7) in vec4 a_instanceMatrix3;
#endif





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


<< EmbeddedCode Area >>

void OutputColor()
{
#if defined(VIEW_NORMAL)
	OutData.color = vec4(a_normal,1.0);
#elif defined(IN_COLOR) && defined(OUT_COLOR)
	OutData.color = vec4(a_color,1.0);
#elif defined(OUT_COLOR)
	OutData.color = uFixColor;
#endif
}

 
void OutputNormal()
{
#if defined(IN_NORMAL) && defined(OUT_NORMAL)
	OutData.normal = a_normal;
#endif
}

void OutputTexcoord()
{
#if defined(IN_TEXCOORD) && defined(OUT_TEXCOORD)
	OutData.texcoord = a_texcoord;
#endif
}

void OutputPosition()
{
#if defined(OUT_PLANE_POSITION) 
	gl_Position = vec4(a_position,1.0);
#elif defined(IN_INSTANCE)
	mat4 vp = scene.Projection * scene.ViewMatrix;
	mat4 instanceMatrix = mat4(a_instanceMatrix0,a_instanceMatrix1,a_instanceMatrix2,a_instanceMatrix3);
	gl_Position = vp * instanceMatrix * vec4(a_position,1.0);
#else
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * vec4(a_position,1.0);
#endif
}

void OutputGBuffer()
{
#if defined(USE_GBUFFER) && defined(IN_NORMAL)
	OutData.position = gl_Position;
	OutData.normal = vec4(a_normal,1);
#elif defined(USE_GBUFFER)
	OutData.position = gl_Position;
	OutData.normal = vec4(1);
#endif
}

void OutputInstance()
{
#if defined(IN_INSTANCE) && defined(OUT_INSTANCE)
	OutData.instanceMatrix0 = a_instanceMatrix0;
	OutData.instanceMatrix1 = a_instanceMatrix1;
	OutData.instanceMatrix2 = a_instanceMatrix2;
	OutData.instanceMatrix3 = a_instanceMatrix3;
#endif
}
void main()
{
#if defined(USE_GBUFFER)
	OutputGBuffer();
#else
	OutputPosition();
	OutputNormal();
#if defined(USE_MATERIAL)
	GetMaterialColor();
#else 
	OutData.color = vec4(1,0,0,1);
#endif
	OutputTexcoord();
	OutputInstance();
#endif
}