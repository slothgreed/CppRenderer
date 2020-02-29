#ifndef EVENTARGS_H
#define EVENTARGS_H

namespace KI
{
class IEventArgs
{
public:
	IEventArgs() {};
	~IEventArgs() {};

private:

};

class EventArgs : public IEventArgs
{
public:
	
	static EventArgs Empty;
	EventArgs() {};
	~EventArgs() {};

private:

};
}
#endif