#ifndef SMOOTHING_COMMAND_H
#define SMOOTHING_COMMAND_H

namespace KI
{
namespace Logic
{
class DLL_EXPORT SmoothingCommandArgs : public ICommandArgs
{
public:
	SmoothingCommandArgs(shared_ptr<IModelNode> pPolygonModel):
		m_pPolygonModel(pPolygonModel) {};
	~SmoothingCommandArgs() {};

	virtual COMMAND_TYPE Type() { return COMMAND_TYPE::SMOOTHING_COMMAND; };
	shared_ptr<IModelNode> m_pPolygonModel;
};

class DLL_EXPORT SmoothingCommand : public ICommand
{
public:
	SmoothingCommand(shared_ptr<SmoothingCommandArgs> args);
	~SmoothingCommand();
	virtual COMMAND_TYPE Type() { return COMMAND_TYPE::SMOOTHING_COMMAND; };
private:

	virtual CommandResult CanExecute() { return CommandResult::Success; };
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};
}
}
#endif // !SMOOTHING_COMMAND_H
