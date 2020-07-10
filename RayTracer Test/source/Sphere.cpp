#include "Sphere.h"
#include "Ray.h"
#include <math.h>
#include <glm/glm.hpp>
Sphere::Sphere(glm::vec3 pos, float radius) : Solid3d(pos)
{

}

Sphere::~Sphere()
{

}

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) // resolution du delta
{
	float delta = b * b - 4 * a *c;
	if (delta < 0) return false;

	if (delta == 0)
		x0 = x1 = -.5 * b / a;
	else {
		float q = (b > 0) ? -0.5 * (b + sqrt(delta)) : -0.5 * (b - sqrt(delta));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);
	return true;
}
bool Sphere::Hit(Ray *  ray)
{
	float t0, t1;

	glm::vec3 L = ray->GetStart() - Sphere::GetPosition();
	glm::vec3 dir = ray->GetDirection();
	float radius2 = Sphere::_Radius * Sphere::_Radius;
	float a = glm::dot(dir, dir);
	float b = 2 * glm::dot(dir, L);
	float c = glm::dot(L, L) - radius2;
	if (!solveQuadratic(a, b, c, t0, t1))return false;

	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0) return false;
	}

	ray->SetHit(ray->GetStart() + t0 * ray->GetDirection());
	return true;
}

bool Sphere::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{

	if (Solid3d::Parse(toParse))
		return true;
	if (toParse.name ==  "Radius")
	{
		this->SetRadius(toParse.value.GetFloat());
		
		return false;
	}
	
}