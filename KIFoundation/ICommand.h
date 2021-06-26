#ifndef ICOMMAND_H
#define ICOMMAND_H
namespace KI
{
namespace Foundation
{

enum class CommandResult
{
	None,
	Success,
	Failed
};

enum COMMAND_TYPE : unsigned int
{
	SUBDIVISION_COMMAND = 0,
	PICK_COMMAND		= 1,
	VOXEL_COMMAND		= 2,
	SAVE_IMAGE_COMMAND	= 3,
	SMOOTHING_COMMAND	= 4,
	VIEW_RESOLUTION_COMMAND = 5,
	COMMAND_TYPE_NUM	= 6
};

class DLL_EXPORT ICommandArgs
{
public:
	ICommandArgs() {};
	~ICommandArgs() {};

	virtual COMMAND_TYPE Type() = 0;
	
private:

};

class DLL_EXPORT ICommand
{
	friend class CommandManager;

public:
	ICommand(shared_ptr<ICommandArgs> args) { m_pArgs = args; };
	~ICommand() {};

	virtual COMMAND_TYPE Type() = 0;

protected:
	virtual CommandResult CanExecute() = 0;
	virtual CommandResult Execute() = 0;
	virtual CommandResult Undo() = 0;

	shared_ptr<ICommandArgs> m_pArgs;

};
}
}
#endif ICOMMAND_H

