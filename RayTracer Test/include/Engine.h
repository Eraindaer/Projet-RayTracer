#pragma once
#ifndef ENGINE_H 
#define ENGINE_H

class Renderer;
class Scene;

class Engine
{
public:
	Engine();
	~Engine();

	bool Init();
	void Run();
	void Stop();
	void Free();

	inline Renderer * GetRd() const { return _Renderer; }
private:
	Scene *		_MainScene;
    Renderer * _Renderer;

};

#endif // !
