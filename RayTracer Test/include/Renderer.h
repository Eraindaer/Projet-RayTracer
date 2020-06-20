#pragma once
#ifndef RENDERER_H
#define RENDERER_H
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
class Scene;
class Solid3d;
class Ray;
class Renderer
{
public:
	Renderer(int w, int h, int d);
	~Renderer();

	void Draw(Scene *  sce);
	
	inline unsigned char * GetRawImage() { return  _RenderBuffer; }
	inline int GetW() const { return  _Width; }
	inline int GetH() const{ return  _Height; }

private:

	glm::vec4  CalculateRay(Scene *  sce, Solid3d *  Origin, Ray *  Previous, int CurDepth);
	glm::vec4  CalculateReflectRay(Scene *  sce, Solid3d *  Origin, Ray *  Previous, int CurDepth);

	Solid3d *	CalculateNeareastIntersect(Scene *  sce,  Ray  * ToTest); // Null If no Object On Trajectory

	unsigned char * _RenderBuffer;
	int				_Width;
	int				_Height;
	int				_Depth;
	// camera 
	glm::vec3		_PosCamera;
	// viewplane

	

};



#endif // !1
