#ifndef IMANIPULATOR_MODEL_H
#define IMANIPULATOR_MODEL_H

namespace KI
{
namespace Asset
{
enum MANIPULATOR_HANDLE
{
	MANIPULATOR_HANDLE_X	= 0,
	MANIPULATOR_HANDLE_Y	= 1,
	MANIPULATOR_HANDLE_Z	= 2,
	MANIPULATOR_HANDLE_NUM	= 3
};
class DLL_EXPORT IManipulatorModel : public IModel
{
public:
	IManipulatorModel() {};
	virtual ~IManipulatorModel() {};

	virtual void Build() = 0;
	virtual void GetBDB(BDB& bdb) override { assert(0); };

private:

};
}
}

#endif IMANIPULATOR_MODEL_H