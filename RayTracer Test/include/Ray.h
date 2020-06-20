#pragma once
#ifndef RAY_H
#define RAY_H
#include <glm/vec3.hpp>

class Ray 
{
public : 
	Ray(glm::vec3 direction, glm::vec3 positionStart = {0,0,0});
	~Ray();

	inline	glm::vec3 GetStart() const { return  _Start; }
	inline	glm::vec3 GetDirection()const { return _Direction; }
	inline	glm::vec3 GetHit() const { return _PointHit; }
	inline	glm::vec3 GetNormaltHit() const { return _NormalHit; }
	inline	glm::vec3 GetInvDir() const { return _InvDirection; }
	inline	int GetSign(int ind) const { if (ind < 3) return sign[ind]; else return sign[2]; }
	inline	void SetHit(glm::vec3 point)  {  _PointHit = point; }
	inline	void SetNormalHit(glm::vec3 vec) { _NormalHit = vec; }

private:
	glm::vec3 _Direction;
	glm::vec3 _InvDirection;
	glm::vec3 _Start;
	glm::vec3 _PointHit;
	glm::vec3 _NormalHit;
	int sign[3];

};

#endif