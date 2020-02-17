#ifndef IMANIPULATOR_MODEL_H
#define IMANIPULATOR_MODEL_H

namespace KI
{

enum MANIPULATOR_HANDLE
{
	MANIPULATOR_HANDLE_X,
	MANIPULATOR_HANDLE_Y,
	MANIPULATOR_HANDLE_Z
};
class IManipulatorModel : public IModel
{
public:
	IManipulatorModel() {};
	virtual ~IManipulatorModel() {};

	virtual void Build() = 0;
	virtual void GetBDB(BDB& bdb) override { assert(0); };

private:

};
}

#endif IMANIPULATOR_MODEL_H