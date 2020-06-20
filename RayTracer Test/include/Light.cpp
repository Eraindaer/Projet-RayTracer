#include "Light.h"

Light::Light() : Object3d()
{

}

Light::~Light()
{
	
}

bool Light::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{
	if (Object3d::Parse(toParse))
		return true;
	if (toParse.name == "Color")
	{
		_Color.r = toParse.value.GetArray()[0].GetFloat();
		_Color.g = toParse.value.GetArray()[1].GetFloat();
		_Color.b = toParse.value.GetArray()[2].GetFloat();
		_Color.a = toParse.value.GetArray()[3].GetFloat();
		return true;
	}
	return false;
}
