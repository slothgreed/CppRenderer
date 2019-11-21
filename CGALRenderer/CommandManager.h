#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H
namespace KI
{
class CommandManager
{
public:
	CommandManager();
	~CommandManager();

	CommandResult Execute(shared_ptr<ICommand> command);
	CommandResult Undo();
	CommandResult Redo();
	int CommandNum();
private:
	stack<shared_ptr<ICommand>> m_pCommandStack;	// for undo.
	stack<shared_ptr<ICommand>> m_pUndoStack;		// for redo.
};
}
#endif