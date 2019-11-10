CGALModel::CGALModel()
{
	SetBDB(BDB());
}

CGALModel::~CGALModel()
{
}

void CGALModel::SetBDB(BDB bdb)
{
	m_bdb = bdb;
}