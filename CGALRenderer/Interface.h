#ifndef INTERFACE_H
#define	INTERFACE_H
namespace KI
{
class IToString
{
public:
	virtual string ToString() = 0;
};

template<typename T>
class IElement
{
public:
	IElement<T>(string key, T value) { m_key = key, m_value = value; }

	virtual string Key() { return m_key; }
	virtual T Value() { return m_value; }

private:
	string m_key;
	T m_value;
};


template<typename T>
class IIterator
{
public:
	virtual bool HasNext() = 0;
	virtual T	 Current() = 0;
	virtual void Next() = 0;
};

}
#endif // HALFEDGE_FACE_H
