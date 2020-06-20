#include "Cube.h"
#include "Ray.h"
#include <math.h>
#include <glm/glm.hpp>
Cube::Cube(glm::vec3 pos) : Solid3d(pos)
{
	_InitMin = false;
	_InitMax = false;
	glm::vec3 cubePos = (GetMax() - GetMin());
	cubePos.x *= 0.5; cubePos.y *= 0.5; cubePos.z *= 0.5;
	SetPosition(cubePos);

}


Cube::~Cube()
{

}


bool Cube::Hit(Ray * RayToTest) // raw code à refaire
{
	/*glm::vec3 invDir = RayToTest->GetInvDir();
	glm::vec3 bounds[2];
	
	bounds[0] = GetMin();
	bounds[1] = GetMax();
	int sign[3];
	sign[0] = (invDir.x < 0);
	sign[1] = (invDir.y < 0);
	sign[2] = (invDir.z < 0);
	float txmin, txmax, tymin, tymax, tzmin, tzmax;

	txmin = (bounds[sign[0]].x - RayToTest->GetStart().x) * invDir.x;
	txmax = (bounds[1 - sign[0]].x - RayToTest->GetStart().x * invDir.x);
	tymin = (bounds[sign[1]].y - RayToTest->GetStart().y * invDir.y);
	tymax = (bounds[1 - sign[1]].y - RayToTest->GetStart().y * invDir.y);

	if ((txmin > tymax) || (tymin > txmax)) {
		return false;
	}
	if (tymin > txmin)
		txmin = tymin;
	if (tymax < txmax)
		txmax = tymax;

	tzmax = (bounds[sign[2]].z - RayToTest->GetStart().z) * invDir.z;
	tzmin = (bounds[1 - sign[2]].z - RayToTest->GetStart().z) * invDir.z;

	if ((txmin > tzmax) || (tzmin > txmax))
		return false;
	if (tzmin > txmin)
		txmin = tzmin;
	if (tzmax < txmax)
		txmax = tzmax;

	if (txmin > txmax) std::swap(txmin, txmax);

	if (txmin < 0) {
		txmin = txmax;
		if (txmin < 0) return false;
	}
	*/

	/*glm::vec3 invDir = RayToTest->GetInvDir();

	float t1, t2, t3, t4, t5, t6;
	t1 = (GetMin().x - RayToTest->GetStart().x) * invDir.x;
	t2 = (GetMax().x - RayToTest->GetStart().x) * invDir.x;
	t3 = (GetMin().y - RayToTest->GetStart().y) * invDir.y;
	t4 = (GetMax().y - RayToTest->GetStart().y) * invDir.y;
	t5 = (GetMin().z - RayToTest->GetStart().z) * invDir.z;
	t6 = (GetMax().z - RayToTest->GetStart().z) * invDir.z;

	float tmin = glm::max(glm::max(glm::min(t1,t2), glm::min(t3,t4)), glm::min(t5, t6));
	float tmax = glm::min(glm::min(glm::min(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

	if (tmax < 0) {
		RayToTest->SetHit(RayToTest->GetStart() + tmax * RayToTest->GetDirection());
		return false;
	}
	if (tmin > tmax) {
		RayToTest->SetHit(RayToTest->GetStart() + tmax * RayToTest->GetDirection());
		return false;
	}*/

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

	return true;
}

void  Cube::CalculNormal()
{
	//glm::vec3 normal = glm::normalize(glm::cross(_Min, _Max));
	
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