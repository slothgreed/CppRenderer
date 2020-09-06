#ifndef ISHADING_H
#define ISHADING_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT IShading : public IShaderChunk
{
public:
	IShading() {};
	virtual ~IShading() {};
	virtual bool IsShading() { return true; }
};

class DLL_EXPORT IHasShading : public IShaderChunk
{
public:
	IHasShading() {};
	virtual ~IHasShading() {};
	virtual bool HasShading() { return true; }
	IShading* GetShading() { return m_pShading.get(); };
protected:
	shared_ptr<IShading> m_pShading;
};

}
}

#endif
