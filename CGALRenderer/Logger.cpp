namespace KI
{
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
	if (level == LOG_LEVEL::ERROR)
	{
		assert(0);
	}
}

void Logger::GLError()
{
	GLenum result = glGetError();
	if (result != GL_NO_ERROR) {
		assert(0);
	}
}
}