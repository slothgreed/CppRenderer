#ifndef IMANIPULATOR_MODEL_H
#define IMANIPULATOR_MODEL_H

namespace KI
{

class IManipulatorModel : IModel
{
public:
	IManipulatorModel() {};
	virtual ~IManipulatorModel() {};

	virtual void Build() = 0;

private:

};
}

#endif IMANIPULATOR_MODEL_H