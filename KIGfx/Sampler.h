#ifndef SAMPLER_H
#define SAMPLER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT Sampler : public IGLObject
{
public:
	struct SamplerData
	{
		GLenum WRAP_S;
		GLenum WRAP_R;
		GLenum WRAP_T;
		GLenum MIN_FILTER;
		GLenum MAG_FILTER;
		//vec4 BORDER_COLOR;	not implemetion
		//GLfloat MIN_LOD;
		//GLfloat MAX_LOD;
		//GLuint LOD_BIAS;
		//GLenum COMPARE_MODE;
		//GLenum COMPARE_FUNC;

		SamplerData()
			:WRAP_S(GL_NONE), WRAP_R(GL_NONE), WRAP_T(GL_NONE),
			MIN_FILTER(GL_NONE), MAG_FILTER(GL_NONE)//,
			//BORDER_COLOR(vec4(0)),
			//MIN_LOD(0), MAX_LOD(0), LOD_BIAS(0),
			//COMPARE_MODE(GL_NONE), COMPARE_FUNC(GL_NONE)
		{
		}
	};
	
	Sampler();
	~Sampler();

	virtual void Bind() override;
	virtual void Generate() override;
	virtual void UnBind() override;
	virtual void Dispose() override;
	void Set(const SamplerData& samplerData);
	bool Compare(const SamplerData& samplerData);
private:
	SamplerData m_samplerData;
};
}
}
#endif // !SAMPLER_H