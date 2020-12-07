#ifndef PROPERTY_H
#define PROPERTY_H

namespace KI
{
namespace Foundation
{


class DLL_EXPORT PropertyValue
{
public:
	PropertyValue() {};
	virtual ~PropertyValue() {};

	virtual bool GetBool() const { assert(0); return false; }
	virtual int GetInt() const { assert(0); return 0; }
	virtual float GetFloat() const { assert(0); return 0.0f; }
	virtual std::string GetString() const { assert(0); return ""; }
	virtual glm::vec2 GetVec2() const { assert(0); return vec2(); }
	virtual glm::vec3 GetVec3() const { assert(0); return vec3(); }
	virtual glm::vec4 GetVec4() const { assert(0); return vec4(); }

	virtual bool IsBool() { return false; }
	virtual bool IsInt() { return false; }
	virtual bool IsFloat() { return false; }
	virtual bool IsString() { return false; }
	virtual bool IsVec2() { return false; }
	virtual bool IsVec3() { return false; }
	virtual bool IsVec4() { return false; }

	virtual std::string GetTypeName() const = 0;
	virtual void SetValue(const PropertyValue& value) = 0;
private:

};

//class IntValue : public PropertyValue
//{
//public:
//	IntValue(int value) : m_value(value);
//	~IntValue() {};
//	virtual int getInt() const { return m_value; };
//	virtual int isInt() const { return true; };
//	virtual std::string typeName() { return "int" };
//	virtual void set(const PropertyValue& p) { m_value = p.getInt() };
//private:
//	int m_value;
//};
#define PROPERTY_VALUE(className, argType)\
class DLL_EXPORT className##Value : public PropertyValue\
{\
public:\
	##className##Value(argType value) : m_value(value){};\
	~##className##Value(){};\
	virtual argType Get##className() const {return m_value;};\
	virtual bool Is##className() const {return true;};\
	virtual std::string GetTypeName() {return #argType;};\
	virtual void SetValue(const PropertyValue& value){m_value = value.Get##className();};\
private:\
	argType m_value;\
};\

PROPERTY_VALUE(Bool, bool);
PROPERTY_VALUE(Int, int);
PROPERTY_VALUE(Float, float);
PROPERTY_VALUE(String, std::string);
PROPERTY_VALUE(Vec2, glm::vec2);
PROPERTY_VALUE(Vec3, glm::vec3);
PROPERTY_VALUE(Vec4, glm::vec4);


class DLL_EXPORT IProperty
{
public:
	IProperty() {};
	~IProperty() {};

	void SetName(const string& name) { m_name = name; }
	void GetName(string* name) { *name = m_name; }

	void SetValue(PropertyValue* value) { m_value = value; }
	PropertyValue* GetValue() { return m_value; }
private:
	string m_name;
	PropertyValue* m_value;
};


}
}
#endif
