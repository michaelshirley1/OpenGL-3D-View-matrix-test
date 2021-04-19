#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O

// include files are in a slightly different location for MacOS

#include <freeglut.h>
#include <glut.h>
#include "Debug/OpenGLGame.tlog/lodepng.h"
#include <math.h>
#include <iostream> 
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp"

class squarez{
public:
	float radius;
	float centre;
	squarez(float inrad, float incentre);
	void drawSquare(int direction);
};