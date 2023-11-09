#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

#include "Point3D.h"
#include "Vector3D.h"
#include "Camera.h"
#include "Texture.h"
#include "BlenderMesh.h"
#include "Scenes.h"

#define PI				3.1415926535897932384626433832795
#define SCREEN_WIDTH	1760
#define SCREEN_HEIGHT	990
#define FPS				120

// tick count as of the start of the program
DWORD start = GetTickCount64();

// global variables for coordinates, angles and scales at program startup
float X = 0;
float Y = 0;
float J = 0;
float K = 0;
float L = 0;
float M = 0;
//float angle = 0.00;

// boolean variables to control scenes
int CURRENT_SCENE_FLAG = 1;
bool sceneOneInitFlag = false;		// SCENE ONE(A)				// DONE
bool launchInitFlag = false;		// SCENE ONE(B)				// DONE
bool leavingEarthInitFlag = false;	// SCENE ONE(OPT)			// DONE
bool onMoonInitFlag = false;		// SCENE TWO(A)+TWO(B)		// DONE
bool leavingMoonInitFlag = false;	// SCENE THREE				// DONE
bool spacePanoramaInitFlag = false;	// SCENE FOUR				// DONE
bool atPlutoInitFlag = false;		// SCENE FIVE				// DONE
bool backAtEarthInitFlag = false;	// SCENE SIX				// DONE
bool mountainInitFlag = false;		// SCENE SEVEN(OPT)			// BUILDING

// initialise GL. probably okay untouched. aspect ratio set to 16:9; see the gluPerspective() line
void initGL() {
	// initialise Blender meshes
	initBlenderMeshes();

	glEnable(GL_DEPTH_TEST);
	glClearColor(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (16.0 / 9.0), 0.1, 1000.0);

	// lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Set material properties
	GLfloat material_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat material_shininess = 0.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

	GLfloat light_position[] = { 10.0, 20.0, 0.0, 0.0 };	// Light position (from top)
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };       // Dimmer diffuse light color
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };       // Dimmer ambient light color
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };      // Specular light color

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void updateUptime(int value) {
	// program uptime
	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - start;

	// SCENE CONTROLS
	if (uptime < 23000) CURRENT_SCENE_FLAG = 1;							// SCENE ONE(A)
	if (uptime > 23000 && uptime < 40000) CURRENT_SCENE_FLAG = 2;		// SCENE ONE(B)
	if (uptime > 40000 && uptime < 56000) CURRENT_SCENE_FLAG = 3;		// SCENE ONE(OPT)
	if (uptime > 56000 && uptime < 73000) CURRENT_SCENE_FLAG = 4;		// SCENE TWO(A)+TWO(B)
	if (uptime > 73000 && uptime < 84000) CURRENT_SCENE_FLAG = 5;		// SCENE THREE
	if (uptime > 84000 && uptime < 100000) CURRENT_SCENE_FLAG = 6;		// SCENE FOUR
	if (uptime > 100000 && uptime < 112500) CURRENT_SCENE_FLAG = 7;		// SCENE FIVE
	if (uptime > 112500 && uptime < 120000) CURRENT_SCENE_FLAG = 8;		// SCENE SIX

	if (uptime > 120000 && uptime < 150000) CURRENT_SCENE_FLAG = 9;		// SCENE SEVEN(OPT)

	// SCENE ONE(A): REVEAL THE SHIP AND ROUNDABOUT LAUNCHPAD
	if (CURRENT_SCENE_FLAG == 1) {
		if (sceneOneInitFlag == false) {
			setCamera();
			initSceneOneTextures();
			dannyFaceTextures();
			dannyBodyTextures();
			engineOn = 0;
			sceneOneInitFlag = true;
		}
		glutDisplayFunc(realSceneOneDisplay);
		glutIdleFunc(realSceneOneIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE ONE(B): SHIP BLASTS OFF FROM LAUNCHPAD
	if (CURRENT_SCENE_FLAG == 2) {
		if (launchInitFlag == false) {
			setCamera();
			delta_Y = 0.00;
			engineOn = 0;
			//initSceneOneTextures();		// since it shares scene objects with SCENE ONE(A)
			launchInitFlag = true;
		}
		glutDisplayFunc(launchDisplay);
		glutIdleFunc(launchIdle);
		glutKeyboardFunc(launchKeyboard);
	}
	// SCENE ONE(OPT): SHIP LEAVES EARTH (also include moon somewhere in this scene)
	if (CURRENT_SCENE_FLAG == 3) {
		if (leavingEarthInitFlag == false) {
			setCamera();
			initLeavingEarthTextures();
			delta_Y = 0.00;
			delta_Z = 0.00;
			angle = 0.00;
			engineOn = 1;
			leavingEarthInitFlag = true;
		}
		glutDisplayFunc(leavingEarthDisplay);
		glutIdleFunc(leavingEarthIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE TWO(A)+TWO(B): LANDING ON MOON
	if (CURRENT_SCENE_FLAG == 4) {
		if (onMoonInitFlag == false) {
			setCamera();
			initOnMoonTextures();
			angle = 0.00;
			delta_Y = 0.00;
			engineOn = 1;
			onMoonInitFlag = true;
		}
		glutDisplayFunc(onMoonDisplay);
		glutIdleFunc(onMoonIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE THREE: LEAVING MOON
	if (CURRENT_SCENE_FLAG == 5) {
		if (leavingMoonInitFlag == false) {
			setCamera();
			initLeavingMoonTextures();
			angle = 0.00;
			delta_Y = 0.00;
			delta_Z = 0.00;
			engineOn = 1;
			leavingMoonInitFlag = true;
		}
		glutDisplayFunc(leavingMoonDisplay);
		glutIdleFunc(leavingMoonIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE FOUR: SPACE PANORAMA
	if (CURRENT_SCENE_FLAG == 6) {
		if (spacePanoramaInitFlag == false) {
			setCamera();
			initSpacePanoramaTextures();
			angle = 0.00;
			delta_X = 0.00;
			delta_Y = 0.00;
			delta_Z = 0.00;
			engineOn = 1;
			spacePanoramaInitFlag = true;
		}
		glutDisplayFunc(spacePanoramaDisplay);
		glutIdleFunc(spacePanoramaIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE FIVE: AT PLUTO AND KICKBACK TO EARTH
	if (CURRENT_SCENE_FLAG == 7) {
		if (atPlutoInitFlag == false) {
			setCamera();
			initAtPlutoTextures();
			delta_X = 0.00;
			delta_Y = 0.00;
			angle = 0.00;
			engineOn = 1;
			atPlutoInitFlag = true;
		}
		glutDisplayFunc(atPlutoDisplay);
		glutIdleFunc(atPlutoIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE SIX: BACK AT EARTH
	if (CURRENT_SCENE_FLAG == 8) {
		if (backAtEarthInitFlag == false) {
			setCamera();
			initBackAtEarthTextures();
			angle = 0.00;
			delta_X = 0.00;
			delta_Y = 0.00;
			delta_Z = 0.00;
			engineOn = 0;
			backAtEarthInitFlag = true;
		}
		glutDisplayFunc(backAtEarthDisplay);
		glutIdleFunc(backAtEarthIdle);
		glutKeyboardFunc(keyboard);
	}
	// SCENE SEVEN(OPT): MOUNTAIN + RKRL
	if (CURRENT_SCENE_FLAG == 9) {
		if (mountainInitFlag == false) {
			setCamera();
			initMountainTextures();
			rickrollSquare.loadRickrollSet();
			delta_X = 0.00;
			delta_Y = 25.00;
			delta_Z = 0.00;
			angle = 0.00;
			engineOn = 0;
			mountainInitFlag = true;
		}
		glutDisplayFunc(mountainDisplay);
		glutIdleFunc(mountainIdle);
		glutKeyboardFunc(keyboard);
	}

	std::cout << "Current uptime (ms): " << uptime << " sceneflag: " << CURRENT_SCENE_FLAG << std::endl;

	glutTimerFunc(1000 / FPS, updateUptime, 0);
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("GAV-3DGPR-ALPHA-1");

	initGL();

	updateUptime(0);

	glutMainLoop();
}