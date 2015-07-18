#ifndef MODELS__OBJ_H_
#define MODELS__OBJ_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "defines.h"

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9


class Model_OBJ
{
  public:
	Model_OBJ();
    float* calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Load(char *filename);	// Loads the model
	void Draw();					// Draws the model on the screen
	void Release();				// Release the model

	float* normals;							// Stores the normals
    float* Faces_Triangles;					// Stores the triangles
	float* vertexBuffer;					// Stores the points which make the object
	long TotalConnectedPoints;				// Stores the total number of connected verteces
	long TotalConnectedTriangles;			// Stores the total number of connected triangles

};





#endif

