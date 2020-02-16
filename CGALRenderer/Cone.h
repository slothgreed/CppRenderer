#ifndef CONE_H
#define CONE_H

namespace KI
{
class Cone : public IPrimitive
{
public:
	Cone();
	~Cone();

	void Build(float radius, float height, int partition);
private:



};

}
#endif CONE_H
