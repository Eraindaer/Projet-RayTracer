#include "Engine.h"
#include "Renderer.h"
#include "Scene.h"
#include "ServiceConfig.h"
#include "ServiceMgr.h"

Engine::Engine()
{
	_MainScene = nullptr;
	_Renderer = nullptr;
}

Engine::~Engine()
{
	if (_Renderer != nullptr)
		delete(_Renderer);
	if (_MainScene != nullptr)
		delete(_MainScene);

}

bool Engine::Init()
{
	new ServiceConfig();
	auto servConf = ServiceMgr::Instance()->GetAService<ServiceConfig>();
	_MainScene = new Scene();
	this->_Renderer= new Renderer(
		atoi(servConf->GetAProperty("width").c_str()),
		atoi(servConf->GetAProperty("height").c_str()),
		atoi(servConf->GetAProperty("depth").c_str()));

	return true;
}

void Engine::Run()
{
	_Renderer->Draw(_MainScene);
}

void Engine::Stop() //  pas vraiment de scene 3d interactive
{

}

void Engine::Free()
{
	if (_Renderer != nullptr)
		delete(_Renderer);
	if (_MainScene != nullptr)
		delete(_MainScene);
	_Renderer = nullptr;
	_MainScene = nullptr;
}