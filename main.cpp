//----------------------------------------------------------------------
//	Best if viewed with tab stops set every 2 columns.
//----------------------------------------------------------------------
//	File: opengl-3D-sample.cpp - Sample 3D OpenGL/GLUT program
//	Origin: Lighthouse3D (heavily modified by Dave Mount)
//
//	This is a sample program that illustrates OpenGL and GLUT. It
//	renders a picture of 36 snowmen. The camera can be moved by dragging
//	the mouse. The camera moves forward by hitting the up-arrow key and
//	back by moving the down-arrow key. Hit ESC, 'q' or 'Q' to exit.
//
//	Warning #1: This program uses the function glutSpecialUpFunc, which
//	may not be available in all GLUT implementations. If your system
//	does not have it, you can comment this line out, but the up arrow
//	processing will not be correct.
//
//	Warning #2: This is a minimalist program. Very little attention has
//	been paid to good programming technique.
//----------------------------------------------------------------------
#define STB_IMAGE_IMPLEMENTATION
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
#include "stb_image.h"
#include "createSquare.h"
#include "decodePNG.h"
// escape key (for exit)
#define ESC 27

std::vector<unsigned char> img;
unsigned w, h;
decodeP decoder;

// Camera position
float x = 0.0, y = -5.0, z = 1.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move
float deltaMoveY = 0.0;
float deltaMoveZ = 0.0;
// Camera direction
float lx = 0.0, ly = 1.0, lz = 0.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging
float deltaAngleZ = 0.0;
// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts
int zDragStart = 0;

//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h)
{
	float ratio = ((float)w) / ((float)h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


void createCube(int x, int y) {
	squarez square1(x, y);
	square1.drawSquare(0);

	squarez square2(x, y);
	square2.drawSquare(1);

	squarez square3(x, y);
	square3.drawSquare(2);

	squarez square4(x, y);
	square4.drawSquare(3);

	squarez square5(x, y);
	square5.drawSquare(4);
}


void update(void){
	
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
	}
	if (deltaMoveY) { // update camera position
		y += deltaMoveY * lx * 0.1;
		x -= deltaMoveY * ly * 0.1;
	}
	if (deltaMoveZ) {
		z = deltaMoveZ * lz * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}


void renderScene(void)
{

	// Clear color and depth buffers
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
		x, y, 1.0,
		x + lx, y + ly, z + lz,
		0.0, 0.0, 1.0);

	// Draw ground
	glBindTexture(GL_TEXTURE_2D, decoder.decodeOneStep("testgrass.jpg"));
	glColor3f(1.0, 1, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(-10.0, -10.0, 0.0);
	glTexCoord2d(20, 0);
	glVertex3f(-10.0, 10.0, 0.0);
	glTexCoord2d(20, 20);
	glVertex3f(10.0, 10.0, 0.0);
	glTexCoord2d(0, 20);
	glVertex3f(10.0, -10.0, 0.0);
	glEnd();

	glPushMatrix();

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glBindTexture(GL_TEXTURE_2D, decoder.decodeOneStep("MakingMap2.png"));
	
	createCube(1, 2);

	createCube(1, 5);

	glPopMatrix();

	glutSwapBuffers(); // Make it all visible
	
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
	switch (key) {
		case 'w': deltaMove = 1.0; break;
		case 's': deltaMove = -1.0; break;
		case 'a': deltaMoveY = 1; break;
		case 'd': deltaMoveY = -1; break;
	}
	
}

void releaseNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
	switch (key) {
	case 'w': deltaMove = 0.0; break;
	case 's': deltaMove = 0.0; break;
	case 'a': deltaMoveY = 0; break;
	case 'd': deltaMoveY = 0; break;
	}

}

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_UP: deltaMove = 1.0; break;
	case GLUT_KEY_DOWN: deltaMove = -1.0; break;
	case GLUT_KEY_LEFT: deltaMoveY = 1; break;
	case GLUT_KEY_RIGHT: deltaMoveY = -1; break;
	}
}

void releaseSpecialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.0; break;
	case GLUT_KEY_DOWN: deltaMove = 0.0; break;
	case GLUT_KEY_LEFT: deltaMoveY = 0.0; break;
	case GLUT_KEY_RIGHT: deltaMoveY = 0.0; break;
	}
}


void mouseMove(int x, int y)
{
	switch (1) {
	case (1): // only when dragging
				// update the change in angle
			deltaAngle = (x - xDragStart) * 0.005;

			// camera's direction is set to angle + deltaAngle
			lx = -sin(angle + deltaAngle);
			ly = cos(angle + deltaAngle);

			deltaAngleZ = (y - zDragStart) * 0.005;

			lz = sin(deltaAngleZ);
		
	}
	
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
			zDragStart = y;
		}
		else { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 1; // no longer dragging
		}
	}
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char** argv)
{
	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1360, 768);
	glutCreateWindow("OpenGL/GLUT Sampe Program");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(renderScene); // (re)display callback
	glutIdleFunc(update); // incremental update 
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(releaseNormalKeys);// process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	
	

	// enter GLUT event processing cycle
	glutMainLoop();



	return 0; // this is just to keep the compiler happy
}

