namespace KI
{
namespace Logic
{

SmoothingCommand::SmoothingCommand(shared_ptr<SmoothingCommandArgs> args)
	: ICommand(args)
{
}

SmoothingCommand::~SmoothingCommand()
{

}

CommandResult SmoothingCommand::Execute()
{
	auto pArgs = static_pointer_cast<SmoothingCommandArgs>(m_pArgs);
	if (pArgs == nullptr)
	{
		return CommandResult::Failed;
	}

	auto pPolygonModel = (((PolygonModelNode*)pArgs->m_pPolygonModel.get()))->GetModel();
	auto pHalfEdgeModel = (HalfEdgeModel*)pPolygonModel;
	SmoothingAlgorithm algorithm(pHalfEdgeModel->GetHalfEdgeDS().get());
	
	bool result = algorithm.Execute();
	if (result)
	{
		pPolygonModel->Update();
		return CommandResult::Success;
	}
	else
	{
		return CommandResult::Failed;
	}
	
}

}
}