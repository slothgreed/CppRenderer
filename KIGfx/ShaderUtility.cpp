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

GLuint ShaderUtility::Link(GLuint vertexId, GLuint tcsId, GLuint tesId, GLuint geomId, GLuint fragId)
{
	GLuint programId = glCreateProgram();

	if (vertexId != 0)
		glAttachShader(programId, vertexId);
	if (tcsId != 0)
		glAttachShader(programId, tcsId);
	if (tesId != 0)
		glAttachShader(programId, tesId);
	if (geomId != 0)
		glAttachShader(programId, geomId);
	if (fragId != 0)
		glAttachShader(programId, fragId);

	if (vertexId != 0)
		glDeleteShader(vertexId);
	if (tcsId != 0)
		glDeleteShader(tcsId);
	if (tesId != 0)
		glDeleteShader(tesId);
	if (geomId != 0)
		glDeleteShader(geomId);
	if (fragId != 0)
		glDeleteShader(fragId);

	glLinkProgram(programId);

	GLint result;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		// The maxLength includes the NULL character
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* errorLog = new GLchar[maxLength];
		glGetProgramInfoLog(programId, maxLength, &maxLength, errorLog);
		Logger::Output(LOG_LEVEL::ERROR, "DefaultShader Link Error");
		delete errorLog;
		errorLog = nullptr;
	}

	return programId;
}

void ShaderUtility::EmbeddedCode(string& code, const string& embeddedCode, const string& embeddedIdentifier)
{
	if (code.empty())
	{
		return;
	}

	int pos = code.find(embeddedIdentifier);
	if (pos == -1)
	{
		return;
	}

	string resultCode = code.substr(0, pos);
	resultCode += embeddedCode + "\n";
	resultCode += code.substr(pos + embeddedIdentifier.size(), code.size());
	code = resultCode;
}

void ShaderUtility::ExpandShaderCode(const string& filePath, string& shaderCode)
{
	vector<string> lines;
	FileUtility::Load(filePath, lines);

	string directoryPath;
	FileUtility::GetDirectoryPath(filePath, directoryPath);
	for (int i = 0; i < lines.size(); i++)
	{
		int pos = lines[i].find("#include");
		if (pos == -1)
		{
			shaderCode += lines[i];
			continue;
		}

		// include ‚ª‚ ‚Á‚½ê‡Ä‹A“Ç‚Ýž‚Ý
		string includePath = directoryPath;
		int startPos = lines[i].find("\"");
		includePath += lines[i].substr(0, startPos);
		int endPos = includePath.find_last_of("\"");
		includePath = includePath.erase(endPos);
		ShaderUtility::Load(includePath, shaderCode);
	}
}

void ShaderUtility::Load(string filePath, string& shaderCode)
{
	ExpandShaderCode(filePath, shaderCode);
	
}
}
}