#ifndef VOXEL_COMMAND_H
#define VOXEL_COMMAND_H
namespace KI
{
class VoxelCommandArgs : public ICommandArgs
{
	friend class VoxelCommand;

public:
	VoxelCommandArgs(IWorkspace* pWorkspace, IPolygonModel* model, const vec3& origin, int partition)
		: m_pWorkspace(pWorkspace), m_pModel(model), m_origin(origin), m_partition(partition) {};
	~VoxelCommandArgs() {};

	virtual COMMAND_TYPE Type() { return VOXEL_COMMAND; }

private:
	IWorkspace* m_pWorkspace;
	IPolygonModel* m_pModel;
	vec3 m_origin;
	int m_partition;
};


class VoxelCommand : public ICommand
{
public:
	VoxelCommand(shared_ptr<ICommandArgs> args);
	~VoxelCommand();

	virtual COMMAND_TYPE Type() { return VOXEL_COMMAND; }
private:

	virtual CommandResult CanExecute();
	virtual CommandResult Execute();
	virtual CommandResult Undo() { assert(0); return CommandResult::Failed; }
};


}
#endif // !VOXEL_COMMAND_H

