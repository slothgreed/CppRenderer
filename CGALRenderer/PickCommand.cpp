namespace KI
{

//#define DEBUG_RENDERING
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

#ifdef DEBUG_RENDERING
void DebugRendering(vec3 near, vec3 far, vec2 screenPosition, Viewport* pViewport, Scene* pScene, const RaycastPickInfo& pickInfo)
{
	Logger::Output(LOG_LEVEL::DEBUG, "Posi" + MathHelper::ToString(screenPosition) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "Scre" + MathHelper::ToString(pViewport->GetScreen()) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "Near" + MathHelper::ToString(near) + ", ");
	Logger::Output(LOG_LEVEL::DEBUG, "Far" + MathHelper::ToString(far) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "Proj" + MathHelper::ToString(pScene->GetCamera()->Projection()) + "\n");
	Logger::Output(LOG_LEVEL::DEBUG, "View" + MathHelper::ToString(pScene->GetCamera()->ViewMatrix()) + "\n");

	{
		auto pRayData = make_shared<RenderData>();
		auto pRayVertexBuffer = make_shared<DefaultVertexBuffer>();
		auto pRayShaderPass = make_shared<DefaultShaderPass>();
		pRayShaderPass->SetFixColor(vec4(0, 0, 1, 1));
		vector<vec3> positions;
		//positions.push_back(pickInfo.GetSelectPosition());
		positions.push_back(near);
		positions.push_back(far);
		pRayVertexBuffer->SetPosition(positions);
		pRayData->SetGeometryData(PRIM_TYPE_LINES, pRayVertexBuffer);
		pRayData->SetShaderPass(pRayShaderPass);
		auto pPrimitiveNode = make_shared<PrimitiveNode>(pRayData);
		pScene->AddModelNode(pPrimitiveNode);
	}
	
	{
		auto pRayData = make_shared<RenderData>();
		auto pRayVertexBuffer = make_shared<DefaultVertexBuffer>();
		auto pRayShaderPass = make_shared<DefaultShaderPass>();
		pRayShaderPass->SetFixColor(vec4(0, 0, 1, 1));
		vector<vec3> positions;
		positions.push_back(pickInfo.GetSelectPosition());
		pRayVertexBuffer->SetPosition(positions);
		pRayData->SetGeometryData(PRIM_TYPE_POINTS, pRayVertexBuffer);
		pRayData->SetShaderPass(pRayShaderPass);
		auto pPrimitiveNode = make_shared<PrimitiveNode>(pRayData);
		pPrimitiveNode->SetState(make_shared<PointState>(5, true));
		pScene->AddModelNode(pPrimitiveNode);
	}
}
#endif // DEBUG_RENDERING

CommandResult PickCommand::Execute()
{
	auto pArgs = static_pointer_cast<PickCommandArgs>(m_pArgs);

	vec3 near = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->m_pViewport->Size().y - pArgs->screenPosition.y, 0),
		pArgs->m_pScene->GetCamera()->ViewMatrix(),
		pArgs->m_pScene->GetCamera()->Projection(),
		pArgs->m_pViewport->GetScreen());

	vec3 far = glm::unProject(
		vec3(pArgs->screenPosition.x, pArgs->m_pViewport->Size().y - pArgs->screenPosition.y, 1),
		pArgs->m_pScene->GetCamera()->ViewMatrix(),
		pArgs->m_pScene->GetCamera()->Projection(),
		pArgs->m_pViewport->GetScreen());


	Ray ray(near, far - near);
	RaycastPickInfo pickInfo(PICK_TYPE::PICK_TYPE_FACE, &ray);

	VisibleModelIterator itr(pArgs->m_pScene.get());
	for (; itr.HasNext(); itr.Next())
	{
		auto pModel = itr.Current().GetModel();
		if (pModel == nullptr)
		{
			continue;
		}
		// TODO
		//pModel->RaycastPick(pickInfo);
		int first;
		int count;
		pickInfo.GetSelectRegion(first, count);
		if (pickInfo.Success())
		{
			itr.Current().AddPartSelect(TOPOLOGY_TYPE_FACE, first, count);
		}
	}


#ifdef DEBUG_RENDERING
	DebugRendering(near, far, pArgs->screenPosition, pArgs->m_pViewport.get(), pArgs->m_pScene.get(), pickInfo);
#endif DEBUG_RENDERING

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