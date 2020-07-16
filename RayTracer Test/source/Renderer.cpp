#define _USE_MATH_DEFINES
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "Light.h"
#include <map>
#include <glm/mat4x4.hpp>
#include <math.h>
#include <iostream>

Renderer::Renderer(int w, int h, int d)
{
	_Width = w;
	_Height = h;
	_Depth = d;
	_RenderBuffer = new unsigned char[w * h * 4];
}

Renderer::~Renderer()
{
	delete(_RenderBuffer);
}

glm::vec3  GetReflective(glm::vec3 IncidenceDir, glm::vec3 Normal)
{
//	float angle  = glm::dot(IncidenceDir , Normal);
	return IncidenceDir - 2 * glm::dot(IncidenceDir, Normal) * Normal;
}

Solid3d *	Renderer::CalculateNeareastIntersect(Scene *  sce, Ray  * ToTest)
{
	Solid3d * ptr = nullptr;
	float dist = 0;
	for (auto i = 0; i < sce->GetObjectsSize(); i++) {
		if ((dist == 0) && (sce->GetSolidObject(i)->Hit(ToTest))) {
			dist = glm::distance(sce->GetSolidObject(i)->GetPosition(), ToTest->GetStart());
			ptr = sce->GetSolidObject(i);
		}
		else if ((dist > glm::distance(sce->GetSolidObject(i)->GetPosition(), ToTest->GetStart())) && (sce->GetSolidObject(i)->Hit(ToTest)))  {
			dist = glm::distance(sce->GetSolidObject(i)->GetPosition(), ToTest->GetStart());
			ptr = sce->GetSolidObject(i);
		}
	}
	return ptr;
}

glm::vec4 Renderer::CalculateReflectRay(Scene *  sce, Solid3d *  Origin, Ray  * Previous, int CurDepth)
{
	glm::vec4 color_final = { 0, 0, 0, 0 };
	Ray reflectRay(GetReflective(Previous->GetDirection(), Previous->GetNormalHit()), Previous->GetHit());
	//Solid3d* obj = CalculateNeareastIntersect(sce, &reflectRay);
	Solid3d* obj = nullptr;
	float angle = (glm::dot(reflectRay.GetDirection(), Previous->GetNormalHit())) > 0 ? glm::dot(reflectRay.GetDirection(), Previous->GetNormalHit()) : 0;
	for (auto indObject = 0; indObject < sce->GetObjectsSize(); indObject++) {
		if ((angle != 0) && (sce->GetSolidObject(indObject) != Origin) && (sce->GetSolidObject(indObject)->Hit(&reflectRay)))
		{
				obj = sce->GetSolidObject(indObject);
				color_final.r += CalculateRay(sce, sce->GetSolidObject(indObject), &reflectRay, 0).r * Origin->GetReflective().r*0.5f;
				color_final.g += CalculateRay(sce, sce->GetSolidObject(indObject), &reflectRay, 0).g * Origin->GetReflective().g*0.5f;
				color_final.b += CalculateRay(sce, sce->GetSolidObject(indObject), &reflectRay, 0).b * Origin->GetReflective().b*0.5f;
		}
	}
	if (CurDepth >= 0) {
		color_final += CalculateReflectRay(sce, obj, &reflectRay, --CurDepth);
	}
	return color_final;
}

glm::vec4 Renderer::CalculateRay(Scene *  sce, Solid3d *  Origin, Ray  * Previous, int CurDepth)
{
	glm::vec4 color_final = Origin->GetEmissive();
	glm::vec3 normal = Previous->GetNormalHit();
	normal = glm::normalize(normal);
	for (auto indLight = 0; indLight < sce->GetLightSize(); indLight++)
	{
		Ray lightRay (sce->GetLight(indLight)->GetPosition() - Previous->GetHit(), Previous->GetHit());
		bool hit = false;
		for (auto indObj = 0; indObj < sce->GetObjectsSize(); indObj++)
		{
			if ((sce->GetSolidObject(indObj)->Hit(&lightRay))
				&& (glm::distance(sce->GetSolidObject(indObj)->GetPosition(), sce->GetLight(indLight)->GetPosition()) < glm::distance(Origin->GetPosition(), sce->GetLight(indLight)->GetPosition())))
			{
				hit = true;
			}
		}
		float angle = glm::dot(lightRay.GetDirection(), normal) > 0 ? glm::dot(lightRay.GetDirection(), normal) : 0;
		if  (!hit) {
			
			float dist = glm::length(lightRay.GetDirection()) * glm::length(normal);
			float coef = (1 / dist) * angle;

			color_final.r += Origin->GetMaterial().r * coef * sce->GetLight(indLight)->GetColor().r;
			color_final.g += Origin->GetMaterial().g * coef * sce->GetLight(indLight)->GetColor().g;
			color_final.b += Origin->GetMaterial().b * coef * sce->GetLight(indLight)->GetColor().b;
		}
	}
	
	if (color_final.r > 1.0) color_final.r = 1.0;
	if (color_final.g > 1.0) color_final.g = 1.0;
	if (color_final.b > 1.0) color_final.b = 1.0;
	
	return color_final;

}

void Renderer::Draw(Scene * sce)
{
	auto colorBackground = sce->GetColorBackground() ;
	auto camera = sce->GetCamera();
	camera->CalculateBottomLeftPixel(_Width, _Height);
	std::map<Ray, Solid3d *>  rayHitMap; // prealoué les ray ? 
	auto width = _Width;
	auto heigh = _Height;
	glm::vec4 color;

	for (auto j = 0; j < _Height; j++)
	{
		for (auto i = 0; i < _Width; i++)
		{
			glm::vec4 color = colorBackground;
			auto dir = camera->CalculateRayDir(i, j);
			Ray ray(dir, camera->GetPosition());

			auto obj = CalculateNeareastIntersect(sce, &ray);

			if (obj != nullptr) {
				color = CalculateRay(sce, obj, &ray, 0) * 0.8f;
				color += CalculateReflectRay(sce, obj, &ray, 0);
			}
			if (color.r > 1.0) color.r = 1.0;
			if (color.g > 1.0) color.g = 1.0;
			if (color.b > 1.0) color.b = 1.0;
			color *= 255;
			_RenderBuffer[4 * (j * _Width + i)] = static_cast<unsigned char>(color.r);
			_RenderBuffer[4 * (j * _Width + i) + 1] = static_cast<unsigned char>(color.g);
			_RenderBuffer[4 * (j * _Width + i) + 2] = static_cast<unsigned char>(color.b);
			_RenderBuffer[4 * (j * _Width + i) + 3] = static_cast<unsigned char>(color.a);
		}
	}
}
