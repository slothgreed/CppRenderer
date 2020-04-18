namespace KI
{

PickCommand::PickCommand(shared_ptr<ICommandArgs> args)
	: ICommand(args)
{

}

PickCommand::~PickCommand()
{

}

CommandResult PickCommand::CanExecute()
{
	if (m_pArgs->Type() != PICK_COMMAND)
	{
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}

CommandResult PickCommand::Execute()
{
	auto pArgs = static_pointer_cast<PickCommandArgs>(m_pArgs);

	vec3 near = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->screenPosition.y, 0),
		pArgs->m_pCamera->ViewMatrix(),
		pArgs->m_pCamera->Projection(),
		pArgs->m_pViewport->GetScreen()
		);

	vec3 far = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->screenPosition.y, 0),
		pArgs->m_pCamera->ViewMatrix(),
		pArgs->m_pCamera->Projection(),
		pArgs->m_pViewport->GetScreen()
	);

	for (int i = 0; i < pArgs->m_pTarget.size(); i++)
	{
		auto pModel = pArgs->m_pTarget[i]->GetModel();
		if (pModel == nullptr)
		{
			continue;
		}

		if (pModel->Type() == IPolygonModel::IsPolygonModel(pModel->Type()))
		{
			auto pPolygonModel = static_pointer_cast<IPolygonModel>(pModel);
			pPolygonModel->GetFaceIndexList();
		}

	}

	assert(0);

	return CommandResult::Failed;
}

}