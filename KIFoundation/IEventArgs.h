#ifndef EVENTARGS_H
#define EVENTARGS_H

namespace KI
{
namespace Foundation
{
class DLL_EXPORT IEventArgs
{
public:
	IEventArgs() {};
	~IEventArgs() {};

private:

};

class DLL_EXPORT EventArgs : public IEventArgs
{
public:
	
	static EventArgs Empty;
	EventArgs() {};
	~EventArgs() {};

private:

};
}
}
#endif