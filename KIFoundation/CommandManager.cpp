namespace KI
{
namespace Foundation
{

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

CommandResult CommandManager::Execute(shared_ptr<ICommand> command)
{
	if (command->CanExecute() == CommandResult::Failed)
	{
		return CommandResult::Failed;
	}

	CommandResult result = command->Execute();
	if (result == CommandResult::Failed)
	{
		return CommandResult::Failed;
	}

	m_pCommandStack.push(command);

	return result;
}

CommandResult CommandManager::Undo()
{
	if (m_pCommandStack.size() == 0)
	{
		CommandResult::Failed;
	}

	auto command = m_pCommandStack.top();
	m_pCommandStack.pop(); // ¸”s‚µ‚½‚çˆÈ~Undo‚Å‚«‚È‚­‚È‚é‚Ì‚ğ–h‚®‚½‚ß‚±‚±‚Å––”ö‚ğíœ

	CommandResult result = command->Undo();
	if (result == CommandResult::Failed)
	{
		assert(0);
		return CommandResult::Failed;
	}

	m_pUndoStack.push(command);

	return result;
}

CommandResult CommandManager::Redo()
{
	if (m_pUndoStack.size() == 0)
	{
		return CommandResult::Failed;
	}

	auto command = m_pUndoStack.top();
	CommandResult result = command->Execute();
	m_pUndoStack.pop(); // ¸”s‚µ‚½‚çˆÈ~Redo‚Å‚«‚È‚­‚È‚é‚Ì‚ğ–h‚®‚½‚ß‚±‚±‚Å––”ö‚ğíœ

	if (result == CommandResult::Failed)
	{
		assert(0);
		return CommandResult::Failed;
	}

	return result;
}

int CommandManager::CommandNum()
{
	return (int)m_pCommandStack.size();
}
}
}
