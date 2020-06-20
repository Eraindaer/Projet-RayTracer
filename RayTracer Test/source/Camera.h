#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Object3d.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


class Camera : public Object3d
{
public :
	Camera();
	~Camera();

	void				CalculateBottomLeftPixel(int width, int heigh);
	glm::vec3			CalculateRayDir(int x, int y); // x is x from pixel width y is y from pixel height

	inline glm::vec3	GetFocus() { return _Focus; }
	inline double		GetFov() { return _Hfov; }
	inline double		GetNear() { return _Dnear; }
	inline double		GetFar() { return _Dfar; }

protected:
	bool				Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse) override;

private :
	glm::vec3 _Focus; // direction ou up vector ? 
	double	  _Hfov;
	double	  _Dnear;
	double	  _Dfar;

	glm::vec3 _PixelBottomLeft;
	glm::vec3 _Qx;
	glm::vec3 _Qy;
};

#endif // ! CAMERA_H
