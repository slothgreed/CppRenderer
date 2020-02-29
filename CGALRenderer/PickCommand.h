#ifndef PICK_COMMAND_H
#define PICK_COMMAND_H

namespace KI
{

enum PICK_TARGET
{
	PICK_TARGET_POINT,
	PICK_TARGET_LINE,
	PICK_TARGET_FACE,
	PICK_TARGET_MANIPULATOR,
};

class PickCommandArgs : public ICommandArgs
{
	friend class PickCommand;

public:
	PickCommandArgs(
		shared_ptr<Viewport> viewport,
		shared_ptr<Camera> pCamera,
		vector<shared_ptr<IModelNode>>& pTarget,
		vec2 position)
	{ 
		m_pViewport = viewport;
		m_pCamera = pCamera;
		m_pTarget = pTarget;
		screenPosition = position;
	};
	~PickCommandArgs() {};

	virtual COMMAND_TYPE Type() { return SUBDIVISION_COMMAND; }

private:
	shared_ptr<Viewport> m_pViewport;
	shared_ptr<Camera> m_pCamera;
	vector<shared_ptr<IModelNode>> m_pTarget;
	vec2 screenPosition;
};

class PickCommand : public ICommand
{

public :
	PickCommand(shared_ptr<ICommandArgs> args);
	~PickCommand();

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}

#endif // !PICK_COMMAND_H
