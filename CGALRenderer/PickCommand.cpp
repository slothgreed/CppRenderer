namespace KI
{

PickCommand::PickCommand(shared_ptr<PickCommandArgs> args)
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
		vec3(pArgs->screenPosition.x, pArgs->screenPosition.y, 1),
		pArgs->m_pCamera->ViewMatrix(),
		pArgs->m_pCamera->Projection(),
		pArgs->m_pViewport->GetScreen()
	);

	Ray ray(near, far - near);
	RaycastPickInfo pickInfo(PICK_TYPE::PICK_TYPE_FACE, &ray);

	for (int i = 0; i < pArgs->m_pTarget.size(); i++)
	{
		auto pModel = pArgs->m_pTarget[i]->GetModel();
		if (pModel == nullptr)
		{
			continue;
		}

		if (IPolygonModel::IsPolygonModel(pModel->Type()))
		{
			auto pPolygonModel = static_pointer_cast<IPolygonModel>(pModel);
			pPolygonModel->RaycastPick(pickInfo);
		}
	}

	if (pickInfo.Success())
	{
		return CommandResult::Success;
	}
	else
	{
		return CommandResult::Failed;
	}
}

}