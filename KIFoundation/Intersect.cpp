namespace KI
{
namespace Foundation
{
Intersect::Intersect()
{
}

Intersect::~Intersect()
{
}


// refer : https://shikousakugo.wordpress.com/2012/06/27/ray-intersection-2/
// Tomas Mollerの交差判定,　クラメルの公式利用
bool Intersect::RayToTriangle(
	const Ray& ray,
	const vec3& p0, const vec3& p1, const vec3& p2,
	vec3& position, float& distance)
{
	auto vector1 = p1 - p0;
	auto vector2 = p2 - p0;
	auto invDirection = -ray.Direction();
	float denominator = MathHelper::CramesDet(vector1, vector2, invDirection);

	// レイと平行かどうか
	//if (denominator <= 0) {
	//	distance = numeric_limits<float>::infinity();
	//	return false;
	//}

	auto rayFormula = ray.Origin() - p0;
	float u = MathHelper::CramesDet(rayFormula, vector2, invDirection) / denominator;
	if (u >= 0 && u <= 1)
	{
		float v = MathHelper::CramesDet(vector1, rayFormula, invDirection) / denominator;
		if (v >= 0 && (u + v <= 1))
		{
			float t = MathHelper::CramesDet(vector1, vector2, rayFormula) / denominator;
			// 距離が負
			if (t < 0)
			{
				return false;
			}

			vec3 ratio = ray.Direction() * t;
			position = ray.Origin() + ratio;
			distance = t;
			return true;
		}
	}

	return false;
}
}
}