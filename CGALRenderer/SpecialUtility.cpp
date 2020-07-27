namespace KI
{

void SpecialUtility::LoadVectorFieldSphere(RenderData* pRenderData)
{
	string filePath = "E:\\MyProgram\\KIProject\\renderapp\\application\\ViewerTest\\vectorfield.txt_b";
	ifstream binaryStream(filePath, ios::in | ios::binary);

	vector<vec3> position;
	vector<vec2> texcoord;
	vector<vec3> vectorField;
	
	float x, y, z;
	// triangles Ç≈äiî[Ç≥ÇÍÇƒÇ¢ÇÈÅB
	while (binaryStream.eof() == false)
	{
		binaryStream.read((char*)&x, sizeof(float));
		binaryStream.read((char*)&y, sizeof(float));
		binaryStream.read((char*)&z, sizeof(float));
		position.push_back(vec3(x, y, z));

		binaryStream.read((char*)&x, sizeof(float));
		binaryStream.read((char*)&y, sizeof(float));
		texcoord.push_back(vec2(x, y));

		binaryStream.read((char*)&x, sizeof(float));
		binaryStream.read((char*)&y, sizeof(float));
		binaryStream.read((char*)&z, sizeof(float));
		vectorField.push_back(vec3(x, y, z));
	}

	binaryStream.close();
	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	pVertexBuffer->SetPosition(position);
	pVertexBuffer->SetTexcoord(texcoord);
	pRenderData->SetGeometryData(PRIM_TYPE_TRIANGLES, pVertexBuffer);
}
}