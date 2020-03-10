namespace KI
{

namespace Gfx
{
string ShaderUtility::m_shaderDirectory;

ShaderUtility::ShaderUtility()
{
}

ShaderUtility::~ShaderUtility()
{
}

GLuint ShaderUtility::Compile(const string& code, GLuint shaderType)
{
	GLuint id = glCreateShader(shaderType);

	const GLchar* sourceCode = code.c_str();
	GLint size = (GLint)code.size();
	glShaderSource(id, 1, &sourceCode, &size);

	glCompileShader(id);
	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		// The maxLength includes the NULL character
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(id, maxLength, &maxLength, errorLog);
		Logger::Output(LOG_LEVEL::ERROR, "DefaultShader Compile Error");
		delete errorLog;
		errorLog = nullptr;
	}

	return id;
}

GLuint ShaderUtility::Link(GLuint vertexId, GLuint fragId)
{
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragId);

	glDeleteShader(vertexId);
	glDeleteShader(fragId);

	glLinkProgram(programId);

	GLint result;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		// The maxLength includes the NULL character
		glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(programId, maxLength, &maxLength, errorLog);
		Logger::Output(LOG_LEVEL::ERROR, "DefaultShader Link Error");
		delete errorLog;
		errorLog = nullptr;
	}

	return programId;
}

}
}