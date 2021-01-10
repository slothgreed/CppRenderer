namespace KI
{
namespace Topology
{

void AdjancyMatrixCSVIO::Output(const std::string& filePath, AdjancyMatrix* pMatrix)
{

	FileWriter writer;

	writer.Open(filePath);

	for (int i = 0; i < pMatrix->RowNum(); i++)
	{
		writer.Write(std::to_string(i) + ",");
		for (int j = 0; j < pMatrix->ColumnNum(i); j++)
		{
			auto pData = pMatrix->Get(i, j);
			writer.Write(std::to_string(pData->GetEnd()));

			if (j == pMatrix->ColumnNum(i) - 1) {
				writer.Write("", true);
			} else {
				writer.Write(",");
			}
		}
	}

	writer.Close();
}


}
}