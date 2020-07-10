#pragma once
#ifndef SCENE_H
#define	SCENE_H
#include <string>
#include <vector>
#include <Object3d.h>
#include <rapidjson/allocators.h>
#include <rapidjson/document.h>
#include <glm/vec4.hpp>
#include <functional>
class Camera;
class Renderer;
class Light;
class Object3d;

class Scene
{
public:
	Scene(std::string propNameScene = "Scene1");
	~Scene();
	
	
	void	 Draw();
	void	ParseObjects(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& obj);
	void	ProcessOnSolid(std::function<void(Solid3d*)>);
	void	ProcessOnLight(std::function<void(Light*)> solidProcess);

	inline void	SetARenderer(Renderer * rd) { _Rd = rd; }
	inline void SetACamera(Camera * camera) { _Camera = camera; }
	inline void AddALight(Light *  lightToAdd) { _LightVec.push_back(lightToAdd); }
	inline void AddAnSolidObject(Solid3d *  objToAdd) { _ObjectVec.push_back(objToAdd); }

	inline Solid3d *	GetSolidObject(int index) { return (_ObjectVec[index]); }
	inline Light *		GetLight(int index) { return (_LightVec[index]); }
	inline Camera  *	GetCamera() { return _Camera; }
	inline int			GetLightSize() { return _LightVec.size(); }
	inline int			GetObjectsSize() { return _ObjectVec.size(); }
	inline glm::vec4	GetColorBackground() { return _BackgroundColor; }

private:
	std::vector<Solid3d*>	_ObjectVec;
	std::vector<Light*>		_LightVec;
	glm::vec4				_BackgroundColor;
	Camera				*	_Camera;
	Renderer *			 _Rd;

};
#endif // !1
