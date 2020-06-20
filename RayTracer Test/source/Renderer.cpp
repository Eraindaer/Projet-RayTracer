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

glm::vec4 color_final;
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
	Solid3d* ptr = nullptr;
	for (auto i = 0; i < sce->GetObjectsSize(); i++) {
		if (sce->GetSolidObject(i)->Hit(ToTest) == true) {
			ptr = sce->GetSolidObject(i);
		}
	}
	return ptr;
}

glm::vec4 Renderer::CalculateReflectRay(Scene *  sce, Solid3d *  Origin, Ray *  Previous, int CurDepth)
{
	glm::vec3 normalLightRay = Previous->GetNormaltHit();
	glm::vec3 incidenceDir = Previous->GetInvDir();
	Ray lightRay(Previous->GetHit(), GetReflective(incidenceDir, normalLightRay));

	color_final.r += Origin->GetReflective().r;
	color_final.g += Origin->GetReflective().g;
	color_final.b += Origin->GetReflective().b;
	color_final.a += Origin->GetReflective().a;

	return color_final;

}

glm::vec4 Renderer::CalculateRay(Scene *  sce, Solid3d *  Origin, Ray *  Previous, int CurDepth)
{
	//color_final = { 0,0,0,0 };

	glm::vec3 normal = Previous->GetHit() - Origin->GetPosition();
	float temp = glm::dot(normal, normal);
	if (temp == 0.0f) {
		return color_final;
	}
	temp = 1.0f / sqrtf(temp);
	normal = temp * normal;

	for (int j = 0; j < sce->GetLightSize(); ++j) {
		auto light = sce->GetLight(j);
		glm::vec3 dist = light->GetPosition() - Previous->GetHit();
		
		if (glm::dot(normal, dist) <= 0.0f) {
			continue;
		}
		float t = sqrtf(glm::dot(dist, dist));
		if (t <= 0.0f) {
			continue;
		}
		Ray lightRay(Previous->GetHit(), (1/t) * dist);

		bool inShadow = false;
		for (int k = 0; k < sce->GetObjectsSize(); ++k) {
			if (Origin->Hit(&lightRay) == true) {
				inShadow = true;
				break;
			}
		}
		
		if (inShadow == false) {
			float magnCamRay = sqrtf(sce->GetCamera()->GetFocus().x * sce->GetCamera()->GetFocus().x +
									 sce->GetCamera()->GetFocus().y * sce->GetCamera()->GetFocus().y + 
									 sce->GetCamera()->GetFocus().z * sce->GetCamera()->GetFocus().z);
			float magnLightRay = sqrtf(lightRay.GetDirection().x* lightRay.GetDirection().x +
									   lightRay.GetDirection().y* lightRay.GetDirection().y +
									   lightRay.GetDirection().z* lightRay.GetDirection().z);
			float lambert = (1 / t) * glm::dot(glm::normalize(dist), normal);
			float facingRatio = glm::dot(sce->GetCamera()->GetFocus(), lightRay.GetDirection()) / magnCamRay*magnLightRay;
			//color_final = CalculateReflectRay(sce, Origin, &lightRay, CurDepth + 1);
			color_final.r += lambert * light->GetColor().r * Origin->GetMaterial().r;
			color_final.g += lambert * light->GetColor().g * Origin->GetMaterial().g;
			color_final.b += lambert * light->GetColor().b * Origin->GetMaterial().b;
			color_final.a += lambert * light->GetColor().a * Origin->GetMaterial().a;
			color_final *= facingRatio;
		}
	}
	return color_final;
	
}

void Renderer::Draw(Scene * sce)
{
	glm::vec4 colorBackground = sce->GetColorBackground();
	auto camera = sce->GetCamera();
	camera->CalculateBottomLeftPixel(_Width, _Height);
	std::map<Ray, Solid3d *>  rayHitMap; // prealoué les ray ? 
	auto width = _Width;
	auto heigh = _Height;
	

	for (auto j = 0; j < _Height; j++)
	{
		for (auto i = 0; i < _Width; i++)
		{	
			glm::vec4 color = colorBackground;
			int level = 0;
			auto dir = camera->CalculateRayDir(i, j);
			unsigned char* tmp = _RenderBuffer;
			Ray ray(dir, camera->GetPosition());

			auto obj = CalculateNeareastIntersect(sce, &ray);

			if (obj != nullptr) {
				color = CalculateRay(sce, obj, &ray, level);
			}

			color *= 255;
			
			_RenderBuffer[4 * (j * _Width + i)] = static_cast<unsigned char>(color.r);
			_RenderBuffer[4 * (j * _Width + i) + 1] = static_cast<unsigned char>(color.g);
			_RenderBuffer[4 * (j * _Width + i) + 2] = static_cast<unsigned char>(color.b);
			_RenderBuffer[4 * (j * _Width + i) + 3] = static_cast<unsigned char>(color.a);
		}
	}
}
