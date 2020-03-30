
layout (std140) uniform SceneData
{
	mat4 Projection;
	mat4 ViewMatrix;
}scene;

layout(location = 0) in vec3 position;

#ifdef IN_NORMAL
layout(location = 1) in vec3 normal;
#endif

#ifdef OUT_NORMAL
out vec3 o_normal;
#endif


#ifdef IN_COLOR
layout(location = 2) in vec3 color;
#endif
#ifdef OUT_COLOR
out vec4 o_color;
#endif

#ifdef IN_TEXCOORD
layout(location = 3) in vec2 texcoord;
#endif
#ifdef OUT_TEXCOORD
out vec2 o_texcoord;
#endif

#ifdef IN_INSTANCE
layout(location = 4) in vec4 instanceMatrix0;
layout(location = 5) in vec4 instanceMatrix1;
layout(location = 6) in vec4 instanceMatrix2;
layout(location = 7) in vec4 instanceMatrix3;
#endif
#ifdef OUT_INSTANCE
out vec4 o_instanceMatrix0;
out vec4 o_instanceMatrix1;
out vec4 o_instanceMatrix2;
out vec4 o_instanceMatrix3;
#endif

uniform vec4 uFixColor;

void OutputColor()
{
#if defined(VIEW_NORMAL)
	o_color = vec4(normal,1.0);
#elif defined(IN_COLOR) && defined(OUT_COLOR)
	o_color = vec4(color,1.0);
#elif defined(OUT_COLOR)
	o_color = uFixColor;
#endif
}

 
void OutputNormal()
{
#if defined(IN_NORMAL) && defined(OUT_NORMAL)
	o_normal = vec3(0.5);
#endif
}

void OutputTexcoord()
{
#if defined(IN_TEXCOORD) && defined(OUT_TEXCOORD)
	o_texcoord = texcoord;
#endif
}

void OutputPosition()
{
#if defined(OUT_PLANE_POSITION) 
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * vec4(position,1.0);
#elif defined(IN_INSTANCE)
	mat4 vp = scene.Projection * scene.ViewMatrix;
	mat4 instanceMatrix = mat4(instanceMatrix0,instanceMatrix1,instanceMatrix2,instanceMatrix3);
	gl_Position = vp * instanceMatrix * vec4(position,1.0);
#else
	mat4 vp = scene.Projection * scene.ViewMatrix;
	gl_Position = vp * vec4(position,1.0);
#endif
}

void OutputGBuffer()
{
#if defined(USE_GBUFFER) && defined(IN_NORMAL)
	o_position = gl_Position;
	o_normal = vec4(normal,1);
#elif defined(USE_GBUFFER)
	o_position = gl_Position;
	o_normal = vec4(1);
#endif
}

void OutputInstance()
{
#if defined(IN_INSTANCE) && defined(OUT_INSTANCE)
	o_instanceMatrix0 = instanceMatrix0;
	o_instanceMatrix1 = instanceMatrix1;
	o_instanceMatrix2 = instanceMatrix2;
	o_instanceMatrix3 = instanceMatrix3;
#endif
}
void main()
{
#if defined(USE_GBUFFER)
	OutputGBuffer();
#else
	OutputPosition();
	OutputNormal();
	OutputColor();
	OutputTexcoord();
	OutputInstance();
#endif
}