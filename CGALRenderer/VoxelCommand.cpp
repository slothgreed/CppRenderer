namespace KI
{

VoxelCommand::VoxelCommand(shared_ptr<ICommandArgs> args)
	: ICommand(args)
{
}

VoxelCommand::~VoxelCommand()
{

}

CommandResult VoxelCommand::CanExecute()
{
	if (m_pArgs->Type() != VOXEL_COMMAND)
	{
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}

CommandResult VoxelCommand::Execute()
{
	auto args = static_pointer_cast<VoxelCommandArgs>(m_pArgs);

	Voxelize pVoxelize;
	vector<vec3> position;
	args->m_pModel->GetPositionList(position);
	pVoxelize.Create(position, args->m_origin, args->m_partition);
	

	vector<vec3> voxelPosition;
	vector<int> indexBuffer;
	pVoxelize.GetVertexList(voxelPosition, indexBuffer);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);
	pVertexBuffer->SetPosition(GL_TRIANGLES, voxelPosition);
	pVertexBuffer->SetIndex(indexBuffer);

	auto pShaderDefine = make_shared<DefaultShaderDefine>();
	pShaderDefine->SetShaderDefine(pVertexBuffer->Layout());
	pShaderDefine->SetUseColor(true);
	auto pShader = ShaderManager::Instance()->FindOrNew(pShaderDefine);

	auto pModelNode = make_shared<PrimitiveNode>(pShader, pVertexBuffer);
	args->m_pWorkspace->AddModelNode(pModelNode);
	
	return CommandResult::Success;
}

}