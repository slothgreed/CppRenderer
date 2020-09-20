#ifndef LOGGER_H
#define LOGGER_H
namespace KI
{
namespace Foundation
{
enum LOG_LEVEL
{
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
};


class DLL_EXPORT Logger
{
public:
	Logger();
	~Logger();
	
	static void Output(LOG_LEVEL level, std::string message);
	static void GLError();
private:

};
}
}
#endif LOGGER_H
