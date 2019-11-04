ShaderUtility::ShaderUtility()
{
}

ShaderUtility::~ShaderUtility()
{
}

void ShaderUtility::GetVertexShaderDefine(VERTEX_LAYOUT layout, string & shaderDefine)
{
	switch (layout)
	{
	case VERTEX_LAYOUT_P:
		break;
	case VERTEX_LAYOUT_PN:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		break;
	case VERTEX_LAYOUT_PC:
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PNC:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		break;
	case VERTEX_LAYOUT_PNCT:
		shaderDefine += VERTEX_SHADER_USE_NORMAL;
		shaderDefine += VERTEX_SHADER_USE_COLOR;
		shaderDefine += VERTEX_SHADER_USE_TEXCOORD;
		break;
	default:
		break;
	}
}


