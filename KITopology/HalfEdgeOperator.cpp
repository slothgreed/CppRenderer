namespace KI
{
namespace Topology
{
HalfEdgeOperator::HalfEdgeOperator()
{
}

HalfEdgeOperator::~HalfEdgeOperator()
{
}

void HalfEdgeOperator::FaceSplit(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdgeFace> face, vec3 position)
{

}




//         v2                    v2
//    Å@  Å^Å_ Å@Å@	      Å@    Å^|Å_
//      Å^  Å@Å_ Å@           Å^  |Å@Å_ 
//    Å^  edge=>Å_          Å^  ^ | Å@ Å_ 
// s  ------------ e  =>  s    ed | op   e
//    Å_  <=op  Å^	        Å_ Å@ | Å@ Å^
//    Å@Å_ Å@ Å^	       Å@ Å_  |  Å^
//      Å@Å_Å^		          Å@Å_|Å^
//         v1		              v1
void HalfEdgeOperator::EdgeFlips(HalfEdgeDS* halfEdgeDS, shared_ptr<HalfEdge> edge)
{
	auto opposite = edge->Opposite();

	// í∏ì_Ç™éùÇ¬ÉGÉbÉWÇ™ÉtÉäÉbÉvëŒè€ÇÃèÍçáÇÕÅAê›íËÇïœçXÇ∑ÇÈÅB
	{
		edge->Start()->SetEdge(opposite->Next());
		opposite->Start()->SetEdge(edge->Next());
	}

	auto v1 = opposite->Next()->End();
	auto v2 = edge->Before()->Start();
	
	// è„ÇÃÉRÉÅÉìÉgÇÃí∏ì_ : sv1 = (s => v1)ÇÃÉGÉbÉW
	auto v2s = edge->Before();
	auto sv1 = opposite->Next();
	auto v1e = opposite->Before();
	auto ev2 = edge->Next();

	// ÉtÉäÉbÉvÉGÉbÉW
	{
		edge->Set(
			v2, v2s, sv1,
			opposite,
			edge->Face());
		edge->Face()->SetEdge(edge);

		opposite->Set(
			v1, v1e, ev2,
			edge,
			opposite->Face()
		);
		opposite->Face()->SetEdge(opposite);
	}

	// ÉtÉäÉbÉvà»äOÇÃÉGÉbÉW
	{
		v2s->SetBefore(edge);
		v2s->SetNext(sv1);

		sv1->SetBefore(v2s);
		sv1->SetNext(edge);

		v1e->SetBefore(opposite);
		v1e->SetNext(ev2);
		
		ev2->SetBefore(v1e);
		ev2->SetNext(opposite);
	}

	if (edge->Next() == edge ||
		opposite->Next() == opposite ||
		v2s->Next() == v2s ||
		sv1->Next() == sv1 ||
		v1e->Next() == v1e ||
		ev2->Next() == ev2)
	{
		int a = 0;
	}
}
}
}
