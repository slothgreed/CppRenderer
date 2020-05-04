namespace KI
{
namespace Asset
{
PrimitiveModel::PrimitiveModel(shared_ptr<IPrimitive> pPrimitive)
{
	m_pPrimitive = pPrimitive;
}

PrimitiveModel::~PrimitiveModel()
{
}

void PrimitiveModel::GetFaceList(vector<vec3>& position, vector<vec3>& normal, vector<vec2> texcoord)
{
	position = m_pPrimitive->Position();
	normal = m_pPrimitive->Normal();
	texcoord = m_pPrimitive->Texcoord();
}

void PrimitiveModel::GetFaceIndexList(vector<int>& index)
{
	index = m_pPrimitive->Index();
}

void PrimitiveModel::RaycastPick(RaycastPickInfo& pickInfo)
{
	if (m_pPrimitive->Index().size() == 0)
	{
		assert(0);
	}
	else
	{
		auto positions = m_pPrimitive->Position();
		auto indexs = m_pPrimitive->Index();
		vec3 position;
		float distance;
		
		if (pickInfo.Type() & PICK_TYPE_FACE)
		{
			for (int i = 0; i < indexs.size(); i += 3)
			{
				GL_TRIANGLES_Iterator itr = GL_TRIANGLES_Iterator(
					m_pPrimitive->GetDrawType(), positions.data(), indexs.size());

				while (itr.HasNext())
				{
					vec3 pos0, pos1, pos2;
					itr.Current(pos0, pos1, pos2);
					bool result = MathHelper::IntersectionRayToTriangle(
						pickInfo.GetRay().Origin(), pickInfo.GetRay().Direction(),
						pos0, pos1, pos2, position, distance);
					if (pickInfo.MinDistance() > distance)
					{
						pickInfo.SetResult(PICK_TYPE_FACE, "Face", 3 * i, 3, distance);
					}
					
					itr.Next();
				}
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


