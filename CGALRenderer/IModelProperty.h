#ifndef IMODEL_PROPERTY_H
#define IMODEL_PROPERTY_H

enum PROPERTY_TYPE
{
	PROPERTY_TYPE_BDB
};

class IModelProperty
{
public:
	IModelProperty() {};
	~IModelProperty() {};

	virtual PROPERTY_TYPE Type() = 0;
	virtual void Draw() = 0;
private:

};

#endif // !IMODEL_PROPERTY_H



