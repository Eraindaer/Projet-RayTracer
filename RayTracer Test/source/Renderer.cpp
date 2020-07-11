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
	for (auto i = 0; i < sce->GetObjectsSize(); ++i) {
		if (sce->GetSolidObject(i)->Hit(ToTest)) {
			ptr = sce->GetSolidObject(i);
			break;
		}
	}
	return ptr;

}

glm::vec4 Renderer::CalculateReflectRay(Scene *  sce, Solid3d *  Origin, Ray  * Previous, int CurDepth)
{
	glm::vec4 color_final;
	Ray reflectiveRay = GetReflective(Previous->GetDirection(), Previous->GetNormalHit());
	float angle = glm::dot(reflectiveRay.GetDirection(), Previous->GetNormalHit());
	Solid3d* ptr = CalculateNeareastIntersect(sce, &reflectiveRay);
	if (ptr != nullptr) {
		color_final += ptr->GetMaterial(();
		if (glm::dot(reflectiveRay.GetDirection(), reflectiveRay.GetNormalHit()) < 0) {
			CalculateReflectRay(sce, Origin, &reflectiveRay, ++CurDepth);
		}
	}
	return color_final;
}

glm::vec4 Renderer::CalculateRay(Scene *  sce, Solid3d *  Origin, Ray  * Previous, int CurDepth)
{
	///Initialisation de la couleur, du statut d'ombre, de la normale et normalisation de la normale du point d'impact
	glm::vec4 color_final = Origin->GetMaterial();
	glm::vec3 normal = Previous->GetNormalHit();

	normal = glm::normalize(normal);
	bool hit = false;

	///L'ensemble des lumières est parcouru pour appliquer la couleur à la surface (ou non)
	for (auto i = 0; i < sce->GetLightSize(); ++i) {
		///Définition du rayon partant du point d'impact jusqu'à la position de la lumière
		Ray lightRay = (sce->GetLight(i)->GetPosition() - Previous->GetHit(), Previous->GetHit());

		///L'ensemble des solides de la scène est parcouru pour vérifier si un objet est entre la surface à vérifier et la lumière en question
		for (auto j = 0; j < sce->GetObjectsSize(); ++j) {
			if ((sce->GetSolidObject(j)->Hit(&lightRay)) && 
				(sce->GetSolidObject(j) != Origin)){/* && 
				(glm::distance(sce->GetSolidObject(j)->GetPosition(), sce->GetLight(i)->GetPosition()) < glm::distance(sce->GetSolidObject(j)->GetPosition(), sce->GetLight(i)->GetPosition())))*/ 
				hit = true;
				break;
			}	
		}
		///La surface est éclairée
		if ((hit == false) && (glm::dot(normal, lightRay.GetDirection()) <= 0)) {
			///Methode 1
			float dist = glm::length(lightRay.GetDirection()) * glm::length(normal);
			float coef = (1 / dist) * glm::dot(lightRay.GetDirection(), normal);
			///Méthode 2
			//float coef = glm::abs(glm::dot(normal, lightRay.GetDirection()));
			///Méthode 3
			//float coef = 1.0f;

			color_final.r *= coef * sce->GetLight(i)->GetColor().r;
			color_final.g *= coef * sce->GetLight(i)->GetColor().g;
			color_final.b *= coef * sce->GetLight(i)->GetColor().b;
		}
		else {
			color_final = Origin->GetEmissive();
		}


		for (auto j = 0; j < sce->GetObjectsSize(); ++j) {
			if ((sce->GetSolidObject(j) != Origin) && //Si l'objet de la scène est différent du pointeur ET
				(sce->GetSolidObject(j)->Hit(&lightRay) == true) && //Si la lumière éclaire cet objet ET 
				(glm::distance(lightRay.GetHit(), Previous->GetHit()) < glm::distance(Previous->GetHit(), sce->GetLight(j)->GetPosition()))) { //Si la distance entre le point d'impact du rayon et le point d'impact de la lumière est inférieure à la distance entre le point d'impact du rayon et la position de la lumière
				lightRay.SetNormalHit(Previous->GetNormalHit());
				Ray reflectiveRay = GetReflective(Previous->GetDirection(), Previous->GetNormalHit());
				float angle = glm::dot(reflectiveRay.GetDirection(), Previous->GetNormalHit());
				if ((angle < 0) || (CurDepth == 5)) {
					color_final = Origin->GetEmissive();
				}

				else {
					color_final *= CalculateRay(sce, Origin, &reflectiveRay, ++CurDepth) * Origin->GetReflective();
				}
			}
		}
	}
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
				color = CalculateRay(sce, obj, &ray, 0);
			}

			color *= 255;
			_RenderBuffer[4 * (j * _Width + i)] = static_cast<unsigned char>(color.r);
			_RenderBuffer[4 * (j * _Width + i) + 1] = static_cast<unsigned char>(color.g);
			_RenderBuffer[4 * (j * _Width + i) + 2] = static_cast<unsigned char>(color.b);
			_RenderBuffer[4 * (j * _Width + i) + 3] = static_cast<unsigned char>(color.a);
		}
	}
}
