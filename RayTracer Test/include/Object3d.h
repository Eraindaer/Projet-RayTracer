#pragma once
#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rapidjson/encodings.h>
class Ray; 

class Object3d // creer une matrice world et un transform plus tard
{
public:
	Object3d(const glm::vec3&  pos = { 0,0,0});
	~Object3d();


	void IterationParse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse);
	
	inline	glm::vec3	GetPosition() { return _Position; }
	inline	void		SetPosition(glm::vec3 pos) { _Position = pos; };
protected:
	virtual bool Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse);

	glm::vec3 _Position;
};


class Solid3d : public Object3d
{
public:
	Solid3d(glm::vec3 pos) : Object3d(pos) {}
	virtual ~Solid3d() {}
	

	virtual bool Hit(Ray * RayToTest) { return false; }


	inline	glm::vec4 GetReflective() const { return _Reflective; }
	inline	glm::vec4 GetMaterial() const { return _Material; }
	inline	glm::vec4 GetEmissive() const { return _Emissive; }
protected:
	 bool Parse(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& toParse) override;

private:
	glm::vec4  _Material;
	glm::vec4  _Emissive;
	glm::vec4  _Reflective;
};


#endif // !1
