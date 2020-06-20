#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include "Object3d.h"
class Light : public Object3d
{
public:
	Light();
	virtual ~Light();

	inline glm::vec4	GetColor()const { return _Color; }
protected:
	bool Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse) override;
protected:
	glm::vec4	_Color;

};

#endif