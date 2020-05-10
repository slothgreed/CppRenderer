uniform vec4 uFixColor; // todo : cpp で読み取り

void GetMaterialColor()
{
#if defined(VIEW_VERTEXCOLOR)
	OutData.color = vec4(a_color,1.0);
#elif defined(VIEW_NORMAL)
	OutData.color = vec4(a_normal,1.0);
#elif defined(VIEW_TEXCOORD)
	OutData.color = vec4(a_texcoord,1.0);
#elif defined(VIEW_DEPTH)
	vec3 pos = scene.Projection * scene.ViewMatrix * vec4(a_position,1.0);
	OutData.color = vec4(pos.z,pos.z,pos.z,1.0);
#elif defined(VIEW_FIXCOLOR)
	OutData.color = uFixColor;
#endif
}

