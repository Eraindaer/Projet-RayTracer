#include "Ray.h"
#include <glm/glm.hpp>
Ray::Ray(glm::vec3 direction, glm::vec3 positionStart)
{
	_Direction = glm::normalize(direction);
	_Start = positionStart;

}

Ray::~Ray()
{

}
