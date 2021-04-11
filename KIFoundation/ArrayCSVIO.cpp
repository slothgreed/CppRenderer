namespace KI
{
namespace Foundation
{
void ArrayCSVIO::Output(const std::string& filePath, const vector<vec3>& value)
{
	FileWriter writer;
	writer.Open(filePath);

	for (int i = 0; i < value.size(); i++)
	{
		writer.Write(
			std::to_string(value[i].x) + "," +
			std::to_string(value[i].y) + "," +
			std::to_string(value[i].z), true);
	}

	writer.Close();
}

}
}