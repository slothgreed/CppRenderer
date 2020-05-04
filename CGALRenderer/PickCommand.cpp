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

int g_first = true;
CommandResult PickCommand::Execute()
{
	auto pArgs = static_pointer_cast<PickCommandArgs>(m_pArgs);

	vec3 near = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->screenPosition.y, 0),
		pArgs->m_pScene->GetCamera()->Projection(),
		pArgs->m_pScene->GetCamera()->ViewMatrix(),
		pArgs->m_pViewport->GetScreen()
		);

	vec3 far = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->screenPosition.y, 1),
		pArgs->m_pScene->GetCamera()->Projection(),
		pArgs->m_pScene->GetCamera()->ViewMatrix(),
		pArgs->m_pViewport->GetScreen()
	);

	Logger::Output(LOG_LEVEL::DEBUG, "Near" + MathHelper::ToString(near)+ ", ");
	Logger::Output(LOG_LEVEL::DEBUG, "Far" + MathHelper::ToString(far) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "Proj" + MathHelper::ToString(pArgs->m_pScene->GetCamera()->Projection()) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "View" + MathHelper::ToString(pArgs->m_pScene->GetCamera()->ViewMatrix()) + "\n");

	Ray ray(near, far - near);
	RaycastPickInfo pickInfo(PICK_TYPE::PICK_TYPE_FACE, &ray);

	auto pModelNodes = pArgs->m_pScene->ModelNodes();
	for (int i = 0; i < pModelNodes.size(); i++)
	{
		auto pModel = pModelNodes[i]->GetModel();
		if (pModel == nullptr)
		{
			continue;
		}

		pModel->RaycastPick(pickInfo);

		int first;
		int count;
		pickInfo.GetSelectRegion(first, count);
		if (pickInfo.Success())
		{
			pModelNodes[i]->AddPartSelect(TOPOLOGY_TYPE_FACE, first, count);
		}
	}

	//if (g_first)
	{
		auto pRayData = make_shared<RenderData>();
		auto pRayVertexBuffer = make_shared<DefaultVertexBuffer>();
		auto pRayMaterial = make_shared<DefaultMaterial>();
		pRayMaterial->SetFixColor(vec4(0, 0, 1, 1));
		vector<vec3> positions;
		positions.push_back(near);
		positions.push_back(far);
		pRayVertexBuffer->SetPosition(positions);
		pRayData->SetGeometryData(GL_LINES,pRayVertexBuffer);
		pRayData->SetMaterial(pRayMaterial);
		auto pPrimitiveNode = make_shared<PrimitiveNode>(pRayData);
		pArgs->m_pScene->AddModelNode(pPrimitiveNode);
		g_first = false;
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