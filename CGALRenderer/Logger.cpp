Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Output(LOG_LEVEL level, string message)
{
	USE_VAR(level);
	printf(message.data());
}

void Logger::GLError()
{
	GLenum result = glGetError();
	if (result != GL_NO_ERROR) {
		assert(0);
	}
}