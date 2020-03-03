#ifndef INTERFACE_H
#define	INTERFACE_H

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>
//#include <boost/foreach.hpp>
//#include <boost/optional.hpp>

namespace KI
{
namespace Foundation
{
class DLL_EXPORT IToString
{
public:
	virtual string ToString() = 0;
};

template<typename T>
class DLL_EXPORT IElement
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
class DLL_EXPORT IIterator
{
public:
	virtual bool	HasNext() = 0;
	virtual T		Current() = 0;
	virtual void	Next() = 0;
};

class DLL_EXPORT IXMLIO
{
public:
	//virtual void ReadFromXML(const boost::property_tree::ptree& tree) = 0;
	//virtual void WriteToXML(const boost::property_tree::ptree& tree) = 0;

};
}
}
#endif // HALFEDGE_FACE_H
