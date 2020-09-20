#ifndef CLEAR_SELECT_COMMAND_H
#define CLEAR_SELECT_COMMAND_H

namespace KI
{
namespace Logic
{

class DLL_EXPORT ClearSelectCommandArgs : public ICommandArgs
{
	friend class ClearSelectCommand;

public:
	ClearSelectCommandArgs(
		shared_ptr<Viewport> pViewport,
		shared_ptr<Scene> pScene,
		vec2 position) :
		m_pViewport(pViewport),
		m_pScene(pScene),
		screenPosition(position) {};

	~ClearSelectCommandArgs() {};

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

private:
	shared_ptr<Viewport> m_pViewport;
	shared_ptr<Scene> m_pScene;
	vec2 screenPosition;
};

class DLL_EXPORT ClearSelectCommand : public ICommand
{

public :
	ClearSelectCommand(shared_ptr<ClearSelectCommandArgs> args);
	~ClearSelectCommand();

	virtual COMMAND_TYPE Type() { return PICK_COMMAND; }

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}
}
#endif // !PICK_COMMAND_H
