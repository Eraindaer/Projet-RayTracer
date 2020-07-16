#include "Cube.h"
#include "Ray.h"
#include <math.h>
#include <glm/glm.hpp>
Cube::Cube(glm::vec3 pos) : Solid3d(pos)
{
	_InitMin = false;
	_InitMax = false;
}


Cube::~Cube()
{

}


bool Cube::Hit(Ray * RayToTest) // raw code à refaire
{
	float tmin = (GetMin().x - RayToTest->GetStart().x) / RayToTest->GetDirection().x;
	float tmax = (GetMax().x - RayToTest->GetStart().x) / RayToTest->GetDirection().x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (GetMin().y - RayToTest->GetStart().y) / RayToTest->GetDirection().y;
	float tymax = (GetMax().y - RayToTest->GetStart().y) / RayToTest->GetDirection().y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax)) {
		return false;
	}

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (GetMin().z - RayToTest->GetStart().z) / RayToTest->GetDirection().z;
	float tzmax = (GetMax().z - RayToTest->GetStart().z) / RayToTest->GetDirection().z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax)) {
		return false;
	}
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	RayToTest->SetHit(RayToTest->GetStart() + tmin * RayToTest->GetDirection());

	if (glm::abs(RayToTest->GetHit().z - _Min.z) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(0, 0, -1));
	else if (glm::abs(RayToTest->GetHit().y - _Min.y) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(0, -1, 0));
	else if (glm::abs(RayToTest->GetHit().x - _Min.x) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(-1, 0, 0));
	else if (glm::abs(RayToTest->GetHit().z - _Max.z) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(0, 0, 1));
	else if (glm::abs(RayToTest->GetHit().y - _Max.y) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(0, 1, 0));
	else if (glm::abs(RayToTest->GetHit().x - _Max.x) < 10e-3)
		RayToTest->SetNormalHit(glm::vec3(1, 0, 0));
		
	return true;
}

void  Cube::CalculNormal()
{
	Cube::SetPosition(glm::vec3{ _Min.x, _Max.y, _Max.z });
}

bool Cube::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{
	if (Solid3d::Parse(toParse))
		return true;

	if (toParse.name == "Min")
	{
		_Min.x = toParse.value.GetArray()[0].GetFloat();
		_Min.y = toParse.value.GetArray()[1].GetFloat();
		_Min.z = toParse.value.GetArray()[2].GetFloat();
		_InitMin = true;
		if (_InitMax == true)
			CalculNormal();
		return true;
	}
	else if (toParse.name == "Max")
	{
		_Max.x = toParse.value.GetArray()[0].GetFloat();
		_Max.y = toParse.value.GetArray()[1].GetFloat();
		_Max.z = toParse.value.GetArray()[2].GetFloat();
		_InitMax = true;
		if (_InitMin == true)
			CalculNormal();
		return true;
	}

	return false;
}