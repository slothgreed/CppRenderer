#ifndef INTERFACE_H
#define	INTERFACE_H

class IToString
{
public:
	virtual string ToString() = 0;
};

template<typename T>
class IIterator
{
public:
	virtual bool HasNext() = 0;
	virtual T	 Current() = 0;
	virtual void Next() = 0;
};


#endif // HALFEDGE_FACE_H
