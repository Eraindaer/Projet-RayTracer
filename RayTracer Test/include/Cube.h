#pragma once
#ifndef CUBE_H
#define	CUBE_H
#include "Object3d.h"

class Cube : public Solid3d
{
public : 
	Cube(glm::vec3 pos = {0,0,0});
	~Cube();

	bool Hit(Ray * RayToTest) override;


	inline	glm::vec3 GetMax() const { return _Max; }
	inline	glm::vec3 GetMin() const { return _Min; }

protected:
	void CalculNormal();
	bool Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse) override;
private:
	bool	  _InitMin;
	bool	  _InitMax;
	glm::vec3 _Point[8];
	glm::vec3 _Max;
	glm::vec3 _Min;

};


#endif // !1
