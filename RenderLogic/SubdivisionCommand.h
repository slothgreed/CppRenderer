#ifndef SUBDIVISION_COMMAND_H
#define SUBDIVISION_COMMAND_H
namespace KI
{
namespace Logic
{
class DLL_EXPORT SubdivisionCommandArgs : public ICommandArgs
{
	friend class SubdivisionCommand;

public:
	SubdivisionCommandArgs(shared_ptr<IPolygonModel> model) { m_pModel = model; };
	~SubdivisionCommandArgs() {};

	virtual COMMAND_TYPE Type() { return SUBDIVISION_COMMAND; }

private:
	shared_ptr<IPolygonModel> m_pModel;
};


class DLL_EXPORT SubdivisionCommand : public ICommand
{
public:
	SubdivisionCommand(shared_ptr<ICommandArgs> args);
	~SubdivisionCommand();

	virtual COMMAND_TYPE Type() { return SUBDIVISION_COMMAND; }
private:

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}
}
#endif // !SUBDIVISION_COMMAND_H

