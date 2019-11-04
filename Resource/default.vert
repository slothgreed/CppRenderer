
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

out vec4 v_color;
void main()
{
	mat4 vp = Projection * ViewMatrix;
	gl_Position = vp * vec4(position,1.0);
#ifdef USE_NORMAL
	v_color = vec4(normal,1.0);
#elif defined(USE_COLOR)
	v_color = vec4(color,1.0);
#else
	v_color = vec4(0,0,0);
#endif

}