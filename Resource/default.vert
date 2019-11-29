
layout (std140) uniform Scene
{
	mat4 Projection;
	mat4 ViewMatrix;
};


layout(location = 0) in vec3 position;
#ifdef USE_NORMAL
layout(location = 1) in vec3 normal;
#endif

#ifdef USE_COLOR
layout(location = 2) in vec3 color;
#endif

#ifdef USE_TEXCOORD
layout(location = 3) in vec2 texcoord;
out vec2 v_texcoord;
#else
out vec4 v_color;
#endif

void main()
{
	mat4 vp = Projection * ViewMatrix;
	gl_Position = vp * vec4(position,1.0);
#ifdef USE_COLOR
	v_color = vec4(color,1.0);
#elif defined(USE_NORMAL)
	v_color = vec4(normal,1.0);
#elif defined(USE_TEXCOORD)
	v_texcoord = texcoord;
#else
	v_color = vec4(1,0,0,1.0);
#endif

}