#pragma once
#ifndef PLANE_H
#define PLANE_H
#include "Object3d.h"
class Plane : public Solid3d
{
public: 
	Plane();
	~Plane();

	virtual bool Hit(Ray * RayToTest) override;
private:

};

#endif // !PLANE
