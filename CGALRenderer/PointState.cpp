namespace KI
{
PointState::PointState()
{
}

PointState::~PointState()
{
}

void PointState::Bind()
{
	glPointSize((GLfloat)m_pointSize);
}

void PointState::UnBind()
{
	glPointSize(1.0f);
}
bool PointState::Compare(const IGLState& state)
{
	if (state.Type() == MATERIAL_TYPE_POINTMATERIAL)
	{
		const PointState* point = dynamic_cast<const PointState*>(&state);
		if (GetPointSize() != point->GetPointSize())
		{
			return false;
		}
	}

	return true;
}
}
