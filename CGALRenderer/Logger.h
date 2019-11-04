#ifndef LOGGER_H
#define LOGGER_H

enum LOG_LEVEL
{
	DEBUG,
	WARNING,
	ERROR
};


class Logger
{
public:
	Logger();
	~Logger();
	
	static void Output(LOG_LEVEL level, std::string message);
	static void GLError();
private:

};

#endif LOGGER_H
