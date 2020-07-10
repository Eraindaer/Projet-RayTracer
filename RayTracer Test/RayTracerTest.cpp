//****************************************************************************************************
// Raytracer test:
// ---------------
//  o Welcome to the raytracing programmation test for redway3d!
//
//  o Please read the test description document associated to this file before starting.
//
//  o This source file contains an empty application skeleton for you to add your own ray-tracing code
//    in it. It starts by reading some input parameters:
//     - The ray-tracing depth: this is the number of recursive ray propagations that must be calculated.
//       A ray-tracer depth of 1 means that one reflection and refraction rays must be propagated in
//       the scene. For each of these rays, shading and shadowing calculations of the hit geometries
//       must occur.
//     - The image dimensions in pixels width x height.
//
//  o Step 1 reads input parameters.
//  o Step 2 initialize timers and the image.
//  o Step 2.2 is yours!
//  o Step <3 saves the results to disk.
//
//****************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm/vec3.hpp>
#include <Windows.h>	
#include <iostream>
#include "Engine.h"
#include "Renderer.h"
// CHECK CONFIG.init
//****************************************************************************************************
//*** Scene description parameters *******************************************************************
//****************************************************************************************************

// color_background: The background color to be returned by any ray that don't hit any scene geometry.
//double color_background[4] = { 0.3, 0.3, 0.4, 1.0 };

// Camera description (looking upward the +z axis).
/*double eye[3] = { 700.0, 100.0, 400.0 }; 
double focus[3] = { 0.0, 50.0, 0.0 }; // direction de ma camera
double hfov = 3.141592 / 5.0;
double dnear = 0.1;
double dfar = 10000.0; // distance de rendu  loin

// List of scene boxes:
int nb_boxes = 5;
glm::vec3 box_min[5] = { { -350.0, -350.0, -10.0 }, { -60.0, -60.0, 30.0 }, { -300.0, -330.0, 0.0 },  { -330.0, -300.0, 0.0 },  { -300.0, 310.0, 0.0 } };
glm::vec3 box_max[5] = { { 350.0, 350.0, 10.0 },    { 60.0, 60.0, 150.0 },   { 330.0, -310.0, 200.0 }, { -310.0, 300.0, 200.0 }, { 330.0, 330.0, 200.0 } };

// Material attributes of boxes:
double box_color[5][4]    = { { 0.5, 0.5, 0.5, 1.0 }, { 0.1, 0.4, 0.1, 1.0 }, { 0.0, 1.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 } };
double box_emissive[5][4] = { { 0.1, 0.1, 0.1, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.1, 0.1, 0.1, 1.0 } };
double box_reflect[5][4]  = { { 0.3, 0.3, 0.3, 1.0 }, { 0.7, 0.7, 0.7, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, { 0.1, 0.1, 0.1, 1.0 } };

// List of scene spheres:
int nb_spheres = 4;
glm::vec3 sphere_center[4] = { { 50.0, -130.0, 80.0 }, { -180.0, 180.0, 100.0 }, { 150.0, 150.0, 45.0 }, { 210.0, -25.0, 65.0 } };
float sphere_radius[4] = { 40.0, 75.0, 50.0, 55.0 };

// Material attributes of spheres:
double sphere_color[4][4]    = { { 0.0, 0.4, 0.4, 1.0 }, { 0.8, 0.8, 0.0, 1.0 }, { 0.8, 0.8, 0.8, 1.0 }, { 0.2, 0.2, 0.0, 1.0 } };
double sphere_emissive[4][4] = { { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };
double sphere_reflect[4][4]  = { { 1.0, 0.6, 0.6, 1.0 }, { 0.1, 0.1, 0.4, 1.0 }, { 0.0, 0.2, 0.0, 1.0 }, { 0.8, 0.8, 0.8, 1.0 } };

// List of scene lights:
int nb_lights = 2;
double light_pos[2][3] = { { 50.0, -500.0, 800.0 }, { -350.0, 250.0, 600.0 } };
double light_color[2][4] = { { 0.8, 0.8, 0.8, 1.0 }, { 0.5, 0.7, 0.5, 1.0 } };*/


//****************************************************************************************************
//*** Helpers ****************************************************************************************
//****************************************************************************************************

void FatalError( const char* message )
{
  fprintf( stderr, "%s\n", message );
  while (1 == 1)
  {

  }
  exit( 1 );
}


//****************************************************************************************************
//*** main routine ***********************************************************************************
//****************************************************************************************************

int main(int argc, char** argv)
{	
	
	// 1) Input parameters:
	// --------------------
	

	int width, height, i;
	
	int j;
	auto eng = new Engine();
	eng->Init();
	unsigned char* image = eng->GetRd()->GetRawImage();
	height  = eng->GetRd()->GetH();
	width = eng->GetRd()->GetW();
	

	// 2.1) Initializing performance counters:
	// ---------------------------------------

	__int64 frequency;
	__int64 start, stop;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency) == 0)
	{
		FatalError("RayTracerTest: Performance counter initialization error. Exiting.\n");
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&start);


	// 2.2) Image processing loop:
	// --------------------------- 

	eng->Run();
	


	// 2.3) Collecting elapsed time:
	// -----------------------------

	QueryPerformanceCounter((LARGE_INTEGER*)&stop);

	float elapsed = 1000.0f * (float)(stop - start) / (float)frequency;

	fprintf(stdout, "RayTracerTest: completed in %.2f ms\n", elapsed);


	// 3) Saving the resulting image to disk:
	// --------------------------------------

	FILE* f = fopen("output.tga", "wb");
	if (!f)
	{
		fprintf(stderr, "RayTracerTest: Can't save output image to disk");
	}

	unsigned char thead[18];

	thead[0] = 0;         // No image id field.
	thead[1] = 0;         // Truecolor image.
	thead[2] = 2;         // Type (RGBA) and compression (no compression).
	*((unsigned short *)(thead + 3)) = 0;         // No colormap.
	*((unsigned short *)(thead + 5)) = 0;         // No colormap.
	thead[7] = 0;         // No colormap.
	*((unsigned short *)(thead + 8)) = 0;         // TARGA device specific offset.
	*((unsigned short *)(thead + 10)) = 0;         // TARGA device specific offset.
	*((unsigned short *)(thead + 12)) = width;     // Image width.
	*((unsigned short *)(thead + 14)) = height;    // Image height.
	thead[16] = 4 << 3;      // Bytes per pixel.
	thead[17] = 0x00;      // First bottom left, alpha bits.

	if (fwrite(thead, 1, 18, f) != 18)
	{
		FatalError("RayTracerTest: Unable to save output image to disk");
	}

	unsigned char* tpixel = (unsigned char*)malloc(width * height * 4);
	if (!tpixel)
	{
		FatalError("RayTracerTest: Unable to allocate image for disk saving.\n");
	}

	// Swap pixels (true color TGA format is using an ABGR encoding):
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			tpixel[4 * (j * width + i)] = image[4 * (j * width + i) + 2];
			tpixel[4 * (j * width + i) + 1] = image[4 * (j * width + i) + 1];
			tpixel[4 * (j * width + i) + 2] = image[4 * (j * width + i)];
			tpixel[4 * (j * width + i) + 3] = image[4 * (j * width + i) + 3];
		}
	}

	if (fwrite(tpixel, 1, width * height * 4, f) != width * height * 4)
	{
		FatalError("RayTracerTest: Unable to save output image to disk");
	}

	free(tpixel);
	char tfoot[26];

	memset(tfoot, 0, 26);
	strcpy(tfoot + 8, "TRUEVISION-XFILE.");

	if (fwrite(thead, 1, 26, f) != 26)
	{
		FatalError("RayTracerTest: Unable to save output image to disk");
	}

	fclose(f);


	// 4) Cleanup:
	// -----------


	delete(eng);
	exit(0);
}

