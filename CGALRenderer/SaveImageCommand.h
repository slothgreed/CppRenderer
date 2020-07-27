#ifndef SAVE_IMAGE_COMMAND_H
#define SAVE_IMAGE_COMMAND_H

namespace KI
{

class SaveImageCommandArgs : public ICommandArgs
{
	friend class SaveImageCommand;
public:
	SaveImageCommandArgs(shared_ptr<IRenderTarget> pRenderTarget, const string& outputPath)
		:
		m_pRenderTarget(pRenderTarget),
	m_outputPath(outputPath){};
	~SaveImageCommandArgs() {};
	virtual COMMAND_TYPE Type() override { return SAVE_IMAGE_COMMAND; }

private:
	shared_ptr<IRenderTarget> m_pRenderTarget;
	string m_outputPath;
};


class SaveImageCommand : public ICommand
{
public:
	SaveImageCommand(shared_ptr<SaveImageCommandArgs> args);
	~SaveImageCommand() {};

private:

	virtual COMMAND_TYPE Type() override { return SAVE_IMAGE_COMMAND; }

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};

}


#endif SAVE_IMAGE_COMMAND_H
