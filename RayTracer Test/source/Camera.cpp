#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
glm::mat4 identity = { 1,0,0,0  ,0,1,0,0, 0,0,1,0 ,0,0,0,1 };
Camera::Camera() : Object3d()
{

}

Camera::~Camera()
{

}


bool Camera::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{


	if (Object3d::Parse(toParse))
		return true;
	if (toParse.name == "Direction")
	{
		_Focus.x = toParse.value.GetArray()[0].GetFloat();
		_Focus.y = toParse.value.GetArray()[1].GetFloat();
		_Focus.z = toParse.value.GetArray()[2].GetFloat();
		return true;
	}
	else if (toParse.name == "Hfov")
	{
		_Hfov = toParse.value.GetFloat();
		return true;
	}
	else if (toParse.name == "Dnear")
	{
		_Dnear = toParse.value.GetFloat();
		return true;
	}
	else if (toParse.name == "Dfar")
	{
		_Dfar = toParse.value.GetFloat();
		return true;
	}
	return false;

}

void				Camera::CalculateBottomLeftPixel(int width, int heigh)
{
	float angle = tan(M_PI * 0.5* _Hfov);
	float  aspectratio = heigh / float(width);
	glm::vec3 VerticalVector{ 0,1,0 }; // ou up vector
	glm::vec3 Focus = GetFocus();
	glm::vec3 origin = GetPosition();
	glm::vec3  T = Focus - origin;//  origin to reference point
	glm::vec3  Tn = glm::normalize(T);
	glm::vec3 b = glm::cross(Tn, VerticalVector);
	glm::vec3 bn = glm::normalize(b);
	glm::vec3 vn = glm::cross(Tn, bn);

	float dist = 1.0f;
	float gx = dist * std::tan(angle / 2);
	float gy = gx * aspectratio;
	_Qx = (2.0f * gx) / (width - 1) * bn;
	_Qy = (2.0f * gy) / (heigh - 1) * vn;
	_PixelBottomLeft = Tn * dist - gx * bn - gy * vn;

	glm::vec3 center = origin + Tn;
}

glm::vec3			Camera::CalculateRayDir(int x, int y)
{
	auto pix = _PixelBottomLeft + _Qx * (x - 1.0f) + _Qy * (y - 1.0f);
	return glm::normalize(pix);
}