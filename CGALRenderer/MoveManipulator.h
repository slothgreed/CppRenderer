#ifndef MOVE_MANIPULATOR_H
#define MOVE_MANIPULATOR_H

namespace KI
{

class MoveManipulator : IManipulatorModel
{
public:
	MoveManipulator();
	~MoveManipulator();

	virtual void Build() override;
private:

};

}


#endif MOVE_MANIPULATOR_H