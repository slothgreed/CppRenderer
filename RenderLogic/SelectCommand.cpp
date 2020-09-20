namespace KI
{
namespace Logic
{
//#define DEBUG_RENDERING
SelectCommand::SelectCommand(shared_ptr<SelectCommandArgs> args)
	: ICommand(args)
{

}

SelectCommand::~SelectCommand()
{

}

CommandResult SelectCommand::CanExecute()
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
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Posi" + MathHelper::ToString(screenPosition) + "\n");
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Scre" + MathHelper::ToString(pViewport->GetScreen()) + "\n");
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Near" + MathHelper::ToString(near) + ", ");
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Far" + MathHelper::ToString(far) + "\n");
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "Proj" + MathHelper::ToString(pScene->GetCamera()->Projection()) + "\n");
	Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, "View" + MathHelper::ToString(pScene->GetCamera()->ViewMatrix()) + "\n");

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

CommandResult SelectCommand::Execute()
{
	auto pArgs = static_pointer_cast<SelectCommandArgs>(m_pArgs);

	vec3 near;
	vec3 far;

	CameraUtility::CalcSceneRay(
		pArgs->m_pScene->GetCamera().get(),
		pArgs->m_pViewport.get(),
		pArgs->screenPosition, &near, &far);

	auto pPickPath = make_shared<PickPath>();
	pPickPath->Initialize(
		pArgs->m_pViewport->Size().x, 
		pArgs->m_pViewport->Size().y);
	pPickPath->ResetPickID(pArgs->m_pScene);
	pPickPath->Draw(pArgs->m_pScene);

	vec2 pos = vec2(pArgs->screenPosition.x, pArgs->m_pViewport->Size().y - pArgs->screenPosition.y);
	PickResult pickResult;
	bool result = pPickPath->GetPickResult(pos, &pickResult);

	auto pModel = pArgs->m_pScene->GetModel(pickResult.objectID);
	auto pShading = ShadingManager::Instance()->GetSystemShading(SYSTEM_SHADING::SYSTEM_SHADING_SELECTION);
	pModel->ClearSelect();

	pModel->AddSelect(PICK_TYPE::PICK_TYPE_OBJECT,
		pShading, pickResult.objectID, (pickResult.primitiveID - 1) * 3, 3);

#ifdef DEBUG_RENDERING
	DebugRendering(near, far, pArgs->screenPosition, pArgs->m_pViewport.get(), pArgs->m_pScene.get(), pickInfo);
#endif DEBUG_RENDERING

	if (result)
	{
		return CommandResult::Success;
	}
	else
	{
		return CommandResult::Failed;
	}
}
}
}