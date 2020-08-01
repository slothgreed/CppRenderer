#ifndef VOXEL_COMMAND_H
#define VOXEL_COMMAND_H
namespace KI
{
namespace Logic
{
class DLL_EXPORT VoxelCommandArgs : public ICommandArgs
{
	friend class VoxelCommand;

public:
	VoxelCommandArgs(Scene* pScene, IPolygonModel* model, int partition)
		: m_pScene(pScene), m_pModel(model), m_partition(partition) {};
	~VoxelCommandArgs() {};

	virtual COMMAND_TYPE Type() { return VOXEL_COMMAND; }

private:
	Scene* m_pScene;
	IPolygonModel* m_pModel;
	int m_partition;
};


class DLL_EXPORT VoxelCommand : public ICommand
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
}
#endif // !VOXEL_COMMAND_H

