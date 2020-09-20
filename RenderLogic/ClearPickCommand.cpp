namespace KI
{
namespace Logic
{
ClearSelectCommand::ClearSelectCommand(shared_ptr<ClearSelectCommandArgs> args)
	: ICommand(args)
{

}

ClearSelectCommand::~ClearSelectCommand()
{

}

CommandResult ClearSelectCommand::CanExecute()
{
	if (m_pArgs->Type() != PICK_COMMAND)
	{
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}

CommandResult ClearSelectCommand::Execute()
{
	auto pArgs = static_pointer_cast<ClearSelectCommandArgs>(m_pArgs);

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