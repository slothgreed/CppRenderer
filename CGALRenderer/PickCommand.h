#ifndef PICK_COMMAND_H
#define PICK_COMMAND_H

namespace KI
{

enum PICK_TARGET
{
	PICK_TARGET_POINT		= 0x01,
	PICK_TARGET_LINE		= 0x02,
	PICK_TARGET_FACE		= 0x04,
	PICK_TARGET_MANIPULATOR	= 0x08,
};

class PickCommandArgs : public ICommandArgs
{
	friend class PickCommand;

public:
	PickCommandArgs(
		shared_ptr<Viewport> pViewport,
		shared_ptr<ICamera> pCamera,
		const vector<shared_ptr<IModelNode>>& pTarget,
		vec2 position)
	{ 
		m_pViewport = pViewport;
		m_pCamera = pCamera;
		m_pTarget = pTarget;
		screenPosition = position;
	};
	~PickCommandArgs() {};

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

private:
	shared_ptr<Viewport> m_pViewport;
	shared_ptr<ICamera> m_pCamera;
	vector<shared_ptr<IModelNode>> m_pTarget;
	vec2 screenPosition;
};

class PickCommand : public ICommand
{

public :
	PickCommand(shared_ptr<PickCommandArgs> args);
	~PickCommand();

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}

#endif // !PICK_COMMAND_H
