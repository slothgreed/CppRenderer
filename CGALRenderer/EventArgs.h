#ifndef EVENTARGS_H
#define EVENTARGS_H


class IEventArgs
{
public:
	IEventArgs() {};
	~IEventArgs() {};

private:

};

class EventArgs : IEventArgs
{
public:
	
	static EventArgs Empty;
	EventArgs() {};
	~EventArgs() {};

private:

};

#endif