#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/refine.h>
#include <CGAL/Polygon_mesh_processing/fair.h>
#include <fstream>
#include <map>
namespace KI
{

SubdivisionCommand::SubdivisionCommand(shared_ptr<ICommandArgs> args)
	: ICommand(args)
{
}

SubdivisionCommand::~SubdivisionCommand()
{

}

CommandResult SubdivisionCommand::CanExecute()
{
	if (m_pArgs->Type() != SUBDIVISION_COMMAND_ARGS)
	{
		return CommandResult::Failed;
	}

	return CommandResult::Success;
}

CommandResult SubdivisionCommand::Execute()
{
	auto args = static_pointer_cast<SubdivisionCommandArgs>(m_pArgs);

	typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
	typedef CGAL::Polyhedron_3<Kernel> Polyhedron;

	Polyhedron p;
	auto model = static_pointer_cast<CGALPolyhedron>(args->m_pModel);

	std::vector<Polyhedron::Facet_handle> Facets;
	std::vector<Polyhedron::Vertex_handle> VertexHandle;

	CGAL::Polygon_mesh_processing::refine(
		*model->GetModel(),
		faces(*model->GetModel()),
		std::back_inserter(Facets),
		std::back_inserter(VertexHandle),
		CGAL::Polygon_mesh_processing::parameters::density_control_factor(2.));

	args->m_pModel->Update();

	return CommandResult::Success;
}

}