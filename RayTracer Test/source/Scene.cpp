#include "Scene.h"
#include "ServiceConfig.h"
#include "ServiceMgr.h"
#include "Camera.h"
#include "FileUtils.h"
#include "Sphere.h"
#include "Cube.h"
#include "Light.h"
#include "Renderer.h"
#include <functional>
#include <algorithm>
#include <iostream>

Scene::Scene(std::string propName)
{
	auto inst = ServiceMgr::Instance();
	auto configService = inst->GetAService<ServiceConfig>();
	auto filepath = configService->GetAProperty(propName);
	if (filepath == "")
		return;

	if (FileUtils::ParseJson(filepath, std::bind(&Scene::ParseObjects, this, std::placeholders::_1)) == false)
	{
		std::cout << "le document ne c'est pas correctement ouvert vérifier le config.init " << " \n erreur dans SCENE constructeur" << std::endl;
	}

}

Scene::~Scene()
{
	for (auto lightIte = _LightVec.begin(); lightIte != _LightVec.end(); ++lightIte)
	{
		delete(*lightIte);
	}
	for (auto objIte = _ObjectVec.begin(); objIte != _ObjectVec.end(); ++objIte)
	{
		delete(*objIte);
	}
	delete(_Camera);
}

void Scene::Draw()
{
	_Rd->Draw(this);
}


void Scene::ParseObjects(rapidjson::GenericMember<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>& obj)
{
	std::string nameobj(obj.name.GetString());
	if (nameobj.find("Sphere") != std::string::npos) //  factory ? 
	{
		auto sph = new Sphere();
		sph->IterationParse(obj);
		AddAnSolidObject(sph);
	}
	else if (nameobj.find("Cube") != std::string::npos )
	{
		auto cb = new Cube();
		cb->IterationParse(obj);
		AddAnSolidObject(cb);
	}
	else if (nameobj.find("Light") != std::string::npos)
	{
		auto l = new  Light();
		l->IterationParse(obj);
		AddALight(l);
	}
	else if (nameobj == "Background")
	{
		_BackgroundColor.r = obj.value.GetArray()[0].GetFloat();
		_BackgroundColor.g = obj.value.GetArray()[1].GetFloat();
		_BackgroundColor.b = obj.value.GetArray()[2].GetFloat();
		_BackgroundColor.a = obj.value.GetArray()[3].GetFloat();
	}

	else if (nameobj == "Camera")
	{
		_Camera = new Camera();
		_Camera->IterationParse(obj);
	}
}

void Scene::ProcessOnSolid(std::function<void(Solid3d*)> solidProcess) 
{
	for (auto obj : _ObjectVec)
		solidProcess(obj);
}

void Scene::ProcessOnLight(std::function<void(Light*)> solidProcess)
{
	for (auto light : _LightVec)
		solidProcess(light);
}