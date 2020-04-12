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
	BDB bdb;
	args->m_pModel->GetBDB(bdb);
	pVoxelize.Create(position, bdb, args->m_partition);
	
	vector<vec3> voxelPosition;
	vector<int> indexBuffer;
	pVoxelize.GetVertexList(voxelPosition, indexBuffer);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetPosition(GL_TRIANGLES, voxelPosition);

	auto pIndexBuffer = make_shared<IndexBuffer>();
	pIndexBuffer->Set(GL_TRIANGLES, indexBuffer);

	auto pMaterial = make_shared<DefaultMaterial>();
	pMaterial->SetFixColor(vec4(1, 0, 0, 1));
	
	auto pModelNode = make_shared<PrimitiveNode>(pVertexBuffer, pIndexBuffer, pMaterial);
	
	args->m_pScene->AddModelNode(pModelNode);
	
	return CommandResult::Success;
}

}