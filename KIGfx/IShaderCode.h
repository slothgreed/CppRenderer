#ifndef ISHADER_CODE_H
#define ISHADER_CODE_H

namespace KI
{
namespace Gfx
{
class IUniform;
class IVertexBuffer;
class IShaderChunk;
class DLL_EXPORT IShaderCode
{
public:

	virtual bool IsGlobalCode() { return false; }	// 構造体などの定義コード
	IShaderCode(const string& filePath) { m_filePath = filePath; };
	virtual ~IShaderCode() {};
	void Load(string& code);

	virtual void GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes) {};
	virtual shared_ptr<IShaderCode> GetVertexBufferCode(shared_ptr<IVertexBuffer> pVertexBuffer) { return nullptr; };
	virtual void GetDefineCode(string& code) {};
	virtual void Initialize(GLuint programId) = 0;
	virtual bool Compare(IShaderCode* pShaderCode) = 0;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) = 0;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) = 0;
protected:
	vector<GLint> m_uniformLocation;
	virtual void BindTexture(GLint activeNumber, GLint uniformId);
	virtual void BindInt(GLint uniformId, int value);
	virtual void BindFloat(GLint uniformId, float value);
	virtual void BindVector3(GLint uniformId, vec3 value);
	virtual void BindVector4(GLint uniformId, vec4 value);
private:

	string m_filePath;
	string m_code;
};

}
}

#endif ISHADER_CODE_H