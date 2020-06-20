#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include "Object3d.h"


class Sphere : public Solid3d
{
public:
	Sphere(glm::vec3 pos, float radius);
	Sphere()  : Solid3d({ 0,0,0 }) { _Radius = 0; }
	~Sphere();
	
	bool	Hit(Ray * ray) override;
	inline void	SetRadius(float r) { _Radius = r; }

protected:

	bool	Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse) override;

private:
	float _Radius;
};

#endif // !1
