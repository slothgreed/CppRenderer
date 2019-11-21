#ifndef ICOMMAND_H
#define ICOMMAND_H
namespace KI
{
enum CommandResult
{
	None,
	Success,
	Failed
};

enum COMMAND_TYPE : unsigned int
{
	SUBDIVISION_COMMAND = 0,
	COMMAND_TYPE_NUM	= 1
};

enum COMMAND_ARGS_TYPE : unsigned int
{
	SUBDIVISION_COMMAND_ARGS = 0,
	COMMAND_ARGS_NUM		 = 1
};

class ICommandArgs
{
public:
	ICommandArgs() {};
	~ICommandArgs() {};

	virtual COMMAND_ARGS_TYPE Type() = 0;
	
private:

};

class ICommand
{
	friend class CommandManager;

public:
	ICommand(shared_ptr<ICommandArgs> args) { m_pArgs = args; };
	~ICommand() {};

	virtual COMMAND_TYPE Type() = 0;

private:
	virtual CommandResult CanExecute() = 0;
	virtual CommandResult Execute() = 0;
	virtual CommandResult Undo() = 0;

protected:
	shared_ptr<ICommandArgs> m_pArgs;

};
}
#endif ICOMMAND_H

