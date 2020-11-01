#ifndef IOBSERVER_H
#define IOBSERVER_H

namespace KI
{
namespace Foundation
{
class DLL_EXPORT IObserver
{
public:
	IObserver() {};
	virtual ~IObserver() {};

	virtual void Update(void* sender, IEventArgs* args) = 0;
private:

}; 

class DLL_EXPORT ISubject
{
public:
	ISubject();
	virtual ~ISubject();

	virtual void AddObserver(IObserver* observer);
	virtual void RemoveObserver(IObserver* observer);
	virtual void Update();
	virtual void Update(IEventArgs* pEventArgs);
	virtual void Clear();
private:

	vector<IObserver*> m_observer;

};
}
}
#endif IOBSERVER_H