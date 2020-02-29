#ifndef LOGIC_EVENT_ARGS_COMMAND_H
#define LOGIC_EVENT_ARGS_COMMAND_H

namespace KI
{

enum LOGIC_EVENT_ARGS_TYPE : unsigned int
{
	TOPOLOGY_MODIFIED_EVENT_ARGS = 0,
	EVENT_ARGS_NUM				 = 1,
};

class TopologyModifiedEventArgs : public IEventArgs
{
public:
	TopologyModifiedEventArgs() {};
	~TopologyModifiedEventArgs() {};
	
private:

};

class ModelAddedEventArgs : public IEventArgs
{
public:
	ModelAddedEventArgs() {};
	~ModelAddedEventArgs() {};
};
}



#endif // !LOGIC_EVENT_ARGS_COMMAND_H
