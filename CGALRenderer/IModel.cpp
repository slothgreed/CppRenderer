IModel::IModel()
{
	SetBDB(BDB());
}

void IModel::SetBDB(BDB bdb)
{
	m_bdb = bdb;
}