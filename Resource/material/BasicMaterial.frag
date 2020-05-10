void GetMaterialColor()
{
#if defined(VIEW_TEXTURE)
	OutputColor = texture2D(uTexture0,InData.texcoord);
#else
	OutputColor = vec4(1,0,0,1);
#endif
}