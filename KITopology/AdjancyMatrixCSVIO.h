#ifndef ADJANCY_MATRIX_CSV_IO_H
#define ADJANCY_MATRIX_CSV_IO_H

namespace KI
{
namespace Topology
{

class AdjancyMatrixCSVIO
{
public:
	AdjancyMatrixCSVIO() {};
	~AdjancyMatrixCSVIO() {};

	static void Output(const std::string& filePath, AdjancyMatrix* pMatrix);
private:

};


}
}


#endif ADJANCY_MATRIX_CSV_IO_H