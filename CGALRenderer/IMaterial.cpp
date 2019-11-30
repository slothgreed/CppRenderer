namespace KI
{

void IMaterial::SetVertexBuffer(shared_ptr<IVertexBuffer> vertexBuffer)
{
	m_pVertexBuffer = vertexBuffer;
}

}