namespace KI
{
namespace Asset
{
PrimitiveModel::PrimitiveModel(shared_ptr<IPrimitive> pPrimitive)
{
	m_pPrimitive = pPrimitive;
}

void PrimitiveModel::GetFaceList(vector<vec3>& position, vector<vec3>& normal, vector<vec3>& color, vector<vec2>& texcoord)
{
	position = m_pPrimitive->Position();
	normal = m_pPrimitive->Normal();
	color = m_pPrimitive->Color();
	texcoord = m_pPrimitive->Texcoord();
}

void PrimitiveModel::GetFaceIndexList(vector<int>& index)
{
	index = m_pPrimitive->Index();
}

void PrimitiveModel::RaycastPick(RaycastPickInfo& pickInfo)
{
	if (m_pPrimitive->Index().size() != 0)
	{
		auto positions = m_pPrimitive->Position();
		auto indexs = m_pPrimitive->Index();
		vec3 position;
		float distance;
		
		if (pickInfo.Type() & PICK_TYPE_FACE)
		{
			TriangleIterator itr = TriangleIterator(
				m_pPrimitive->GetDrawType(), positions.data(), indexs.data(), indexs.size());

			while (itr.HasNext())
			{
				vec3 pos0, pos1, pos2;
				itr.Current(&pos0, &pos1, &pos2);
				bool result = MathHelper::IntersectionRayToTriangle(
					pickInfo.GetRay().Origin(), pickInfo.GetRay().Direction(),
					pos0, pos1, pos2, position, distance);
				if (result == true &&
					pickInfo.MinDistance() > distance)
				{
					pickInfo.SetResult(PICK_TYPE_FACE, "Face", 3 * itr.Index(), 3, position, distance);
				}

				itr.Next();
			}
		}
		else
		{
			assert(0);
		}
	}
}
}
}


