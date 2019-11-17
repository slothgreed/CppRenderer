#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
public:
	IObserver() {};
	~IObserver() {};

	virtual void Update(void* sender, shared_ptr<EventArgs> args) = 0;
private:

}; 

class ISubject
{
public:
	ISubject();
	~ISubject();

	virtual void AddObserver(IObserver* observer);
	virtual void RemoveObserver(IObserver* observer);
	virtual void Update();
	virtual void Clear();
private:

	vector<IObserver*> m_observer;

};

#endif IOBSERVER_H