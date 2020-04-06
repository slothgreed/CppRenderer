namespace KI
{
namespace Renderer
{
DefaultShader::DefaultShader()
{
}

DefaultShader::~DefaultShader()
{
}

void DefaultShader::Initialize()
{
	BindScene();
	BindLight();
	FetchUniformLocation();
}

void DefaultShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "SceneData");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::BindLight()
{
	GLint lightBlock = glGetUniformBlockIndex(m_programId, "LightData");
	glUniformBlockBinding(m_programId, lightBlock, LIGHT_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::FetchUniformLocation()
{
	m_uniformLocation.resize(DEFAULT_UNIFORM_NUM);
	m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(m_programId, "uTexture0");
	m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR]	 = glGetUniformLocation(m_programId, "uFixColor");
	Logger::GLError();
}

void DefaultShader::Bind(shared_ptr<IUniform> pUniform)
{
	if (pUniform == nullptr)
	{
		return;
	}

	if (pUniform->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		m_uniformParameter = static_pointer_cast<DefaultUniform>(pUniform);
	}
	else
	{
		assert(0);
		return;
	}

	shared_ptr<DefaultVertexCode> pVertexCode;
	shared_ptr<DefaultFragCode> pFragCode;
	if (BuildInfo()->GetShaderCode(SHADER_PROGRAM_VERTEX)->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT &&
		BuildInfo()->GetShaderCode(SHADER_PROGRAM_FRAG)->Type() == SHADER_TYPE::SHADER_TYPE_DEFAULT)
	{
		pVertexCode = static_pointer_cast<DefaultVertexCode>(BuildInfo()->GetShaderCode(SHADER_PROGRAM_VERTEX));
		pFragCode = static_pointer_cast<DefaultFragCode>(BuildInfo()->GetShaderCode(SHADER_PROGRAM_FRAG));

	}
	else
	{
		assert(0);
		return;
	}

	if (pVertexCode->UseColor() == false &&
		pVertexCode->ViewNormal() == false &&
		pVertexCode->UseTexcoord() == false)
	{
		BindFixColor();
	}

	if (pFragCode->UseTexture0() == true)
	{
		if (m_uniformParameter->GetTexture() == nullptr)
		{
			assert(0);
			return;
		}
		else
		{
			m_uniformParameter->GetTexture()->Begin();
			BindColorTexture();
		}
	}

}

void DefaultShader::UnBind()
{
	if (m_uniformParameter == nullptr)
	{
		return;
	}

	if (m_uniformParameter->GetTexture() != nullptr)
	{
		m_uniformParameter->GetTexture()->End();
	}
}

void DefaultShader::BindColorTexture()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[DEFAULT_UNIFORM_COLOR_TEXTURE]);
}

void DefaultShader::BindFixColor()
{
	if (m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindVector4(m_uniformLocation[DEFAULT_UNIFORM_FIX_COLOR], m_uniformParameter->FixColor());
}

}
}