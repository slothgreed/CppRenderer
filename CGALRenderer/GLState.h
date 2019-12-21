#ifndef IRASTER_STATE_H
#define IRASTER_STATE_H

namespace KI
{

class IGLState
{
public:
	IGLState() {};
	~IGLState() {};
	virtual const STATE_TYPE Type() const = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual bool Compare(const IGLState& state) = 0;

private:

};

class IRasterState : public IGLState
{
public:
	IRasterState() {};
	~IRasterState() {};

private:

};


}

#endif IRASTER_STATE_H
