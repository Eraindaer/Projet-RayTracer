#include "Object3d.h"

Object3d::Object3d(const glm::vec3 & pos)
{
	_Position = pos;
}

Object3d::~Object3d()
{

}



void Object3d::IterationParse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{
	for (auto& m : toParse.value.GetObject())
	{
		Parse(m);
	}
}
bool Object3d::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{
	if (toParse.name == "Position")
	{
		_Position.x = toParse.value.GetArray()[0].GetFloat();
		_Position.y = toParse.value.GetArray()[1].GetFloat();
		_Position.z = toParse.value.GetArray()[2].GetFloat();
		return true;
	}
	return false;

}

bool Solid3d::Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse)
{
	if (Object3d::Parse(toParse))
		return true;

	if (toParse.name == "Material")
	{
		_Material.r = toParse.value.GetArray()[0].GetFloat();
		_Material.g = toParse.value.GetArray()[1].GetFloat();
		_Material.b = toParse.value.GetArray()[2].GetFloat();
		_Material.a = toParse.value.GetArray()[3].GetFloat();
		return true;
	}
	else if (toParse.name == "Emissive")
	{
		_Emissive.r = toParse.value.GetArray()[0].GetFloat();
		_Emissive.g = toParse.value.GetArray()[1].GetFloat();
		_Emissive.b = toParse.value.GetArray()[2].GetFloat();
		_Emissive.a = toParse.value.GetArray()[3].GetFloat();
		return true;
	}
	else if (toParse.name == "Reflective")
	{
		_Reflective.r = toParse.value.GetArray()[0].GetFloat();
		_Reflective.g = toParse.value.GetArray()[1].GetFloat();
		_Reflective.b = toParse.value.GetArray()[2].GetFloat();
		_Reflective.a = toParse.value.GetArray()[3].GetFloat();
		return true;
	}
	return false;
}