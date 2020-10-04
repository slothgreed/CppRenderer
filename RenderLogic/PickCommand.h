#ifndef PICK_COMMAND_H
#define PICK_COMMAND_H

namespace KI
{
namespace Logic
{
enum PICK_TARGET
{
	PICK_TARGET_POINT		= 0x01,
	PICK_TARGET_LINE		= 0x02,
	PICK_TARGET_FACE		= 0x04,
	PICK_TARGET_MANIPULATOR	= 0x08,
};

class DLL_EXPORT SelectCommandArgs : public ICommandArgs
{
	friend class PickCommand;

public:
	SelectCommandArgs(
		shared_ptr<Viewport> pViewport,
		shared_ptr<Scene> pScene,
		vec2 position) :
		m_pViewport(pViewport),
		m_pScene(pScene),
		screenPosition(position) {};

	~SelectCommandArgs() {};

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

private:
	shared_ptr<Viewport> m_pViewport;
	shared_ptr<Scene> m_pScene;
	vec2 screenPosition;
};

class DLL_EXPORT PickCommand : public ICommand
{

public :
	PickCommand(shared_ptr<SelectCommandArgs> args);
	~PickCommand();

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

protected:
	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}
}
#endif // !PICK_COMMAND_H
