#ifndef ICONTROLLER_H
#define ICONTROLLER_H
namespace KI
{
namespace Foundation
{
enum CONTROLER_TYPE : unsigned int
{
	CAMERA_CONTROLER,
	CONTROLER_TYPE_NUM
};

class DLL_EXPORT IControllerArgs
{
public:
	IControllerArgs() {};
	~IControllerArgs() {};

private:

};
class Mouse;
class DLL_EXPORT IController
{
public:
	IController() {};
	~IController() {};

	virtual void SetArgs(std::shared_ptr<IControllerArgs> value) { assert(0); }
	virtual bool Down(const Mouse&  mouse) { return false; };
	virtual bool Up(const Mouse&  mouse) { return false; };
	virtual bool Move(const Mouse&  mouse) { return false; };
	virtual bool Wheel(const Mouse&  mouse) { return false; }
private:

};
}
}
#endif ICONTROLLER_H