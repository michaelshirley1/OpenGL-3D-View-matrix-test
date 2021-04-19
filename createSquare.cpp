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
#include "createSquare.h"


squarez::squarez(float inrad, float incentre) {
	squarez::radius = inrad;
	squarez::centre = incentre;
}
void squarez::drawSquare(int direction) {
	switch (direction) {
	case 0:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre, centre, centre + radius);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre, centre, centre);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(radius + centre, centre, centre);
		glTexCoord2d(0.5, 0);
		glVertex3f(centre + radius, centre, centre + radius);
		glEnd();
	case 1:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre , centre, centre+ radius);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre, centre, centre);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(centre, radius + centre, centre);
		glTexCoord2d(0.5, 0);
		glVertex3f(  centre, centre + radius, centre + radius );
		glEnd();
	case 2:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre, radius + centre, centre + radius);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre, radius + centre, centre);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(radius + centre, radius + centre, centre);
		glTexCoord2d(0.5, 0);
		glVertex3f(centre + radius, radius + centre, centre + radius);
		glEnd();
	case 3:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre + radius, centre + radius, centre + radius);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre + radius, centre + radius, centre);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(centre + radius, centre, centre);
		glTexCoord2d(0.5, 0);
		glVertex3f(centre + radius, centre, centre + radius);
		glEnd();

	case 4:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre + radius, centre + radius, centre);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre + radius, centre, centre);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(centre, centre, centre);
		glTexCoord2d(0.5, 0);
		glVertex3f(centre, centre + radius , centre);
		glEnd();
	case 5:
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(centre + radius, centre + radius, centre + radius);
		glTexCoord2d(0, 0.5);
		glVertex3f(centre + radius, centre, centre + radius);
		glTexCoord2d(0.5, 0.5);
		glVertex3f(centre, centre, centre + radius);
		glTexCoord2d(0.5, 0);
		glVertex3f(centre, centre + radius, centre + radius);
		glEnd();
	}
	 
	
}
