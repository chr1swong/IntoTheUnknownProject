#include <Windows.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>

#include "Point3D.h"
#include "Vector3D.h"
#include "Camera.h"
#include "ScenesObjects.h"

#define PI				3.1415926535897932384626433832795
#define FPS				120

DWORD programStart = GetTickCount64();
DWORD lastUpdateTime = 0;
DWORD lastUpdateTime2 = 0;

Camera sceneCam;

// global variables
float delta_X = 0.00;
float delta_Y = 0.00;
float delta_Z = 0.00;
float angle = 0.00;
float limbWaveAngle1 = 65.00;
float limbWaveAngle2 = 125.00;
int currentImageIndex = 0;
bool decrementing = false;
bool limbWaveIncrementing1 = true;
bool limbWaveIncrementing2 = true;
bool monsterIsOut = false;
int engineOn = 0;

// needed for manual keyboard control
void keyboard(unsigned char key, int x, int y) {
	sceneCam.Update(key);
}

// specifically for launch scene only
void launchKeyboard(unsigned char key, int x, int y) {
	sceneCam.Update(key, 0.2);
}

// needed to initialise the camera
void setCamera() {
	sceneCam.Set(Point3D(25.0, 2.0, 25.0), Point3D(0.0, 0.0, 0.0), Vector3D(0.0, 1.0, 0.0));
}

// ===================== SCENES ======================= //

void realSceneOneDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// draw the scene's objects starting here!!

	// TEST SKY
	// draw the sky background first
	glColor3ub(255, 255, 255);
	drawSkybox();
	// END TEST SKY

	// draw the rest of the scene's objects starting here!!
	glPushMatrix();
	glTranslated(-10.0, 0.0, -10.0);
	drawBaseplate();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	rebalancer.drawSquare();
	glPopMatrix();

	// SCENERY: LOCK!
	{
		glPushMatrix();
		glTranslated(-20.0, 0.0, -49.0);
		mountainRange();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-60.0, 0.0, 10.0);
		glPushMatrix();
		glRotated(90.0, 0.0, 1.0, 0.0);
		mountainRange();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(20.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(-15.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-35.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(26.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, -30.0);
		glPushMatrix();
		glRotated(101.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, 45.0);
		glPushMatrix();
		glRotated(120.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
	//glTranslated(-30.0, 5.0, -30.0);
	glTranslated(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, delta_Y, 0.0);
	drawClockTower();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//glTranslated(-30.0, 3.0, -30.0);
	glTranslated(0.0, -12.4, 0.0);
	glPushMatrix();
	//glRotated(angle, 0.0, 1.0, 0.0);
	glScaled(1.5, 1.5, 1.5);
	drawSpaceStation();
	glPopMatrix();
	glPopMatrix();

	// DANNY'S HUMANOIDS
	{
		glPushMatrix();

		glScaled(0.10, 0.10, 0.10);
		glTranslated(0.0, 13.0, -180.0 + delta_Z);

		glPushMatrix();
		glRotated(-45.0, 0.0, 1.0, 0.0);
		danny1(limbWaveAngle1, limbWaveAngle2);
		glPopMatrix();

		glPushMatrix();
		glRotated(-45.0, 0.0, 1.0, 0.0);
		danny2(limbWaveAngle1, limbWaveAngle2);
		glPopMatrix();

		glPushMatrix();
		glRotated(-45.0, 0.0, 1.0, 0.0);
		danny3(limbWaveAngle2, limbWaveAngle1);
		glPopMatrix();

		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}
void realSceneOneIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	//delta_X += 0.10;
	//delta_Y += 0.10;
	delta_Z += 0.10;
	angle += 0.02;

	if (angle > 360.00) {
		angle = 0.00;
	}

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	// FOR LIMBS ONLY
	{
		if (limbWaveIncrementing1) {
			if (limbWaveAngle1 < 125.00) {
				limbWaveAngle1 += 1.0;
			}
			if (limbWaveAngle1 >= 125.00) {
				limbWaveAngle1 = 125.00;
				limbWaveIncrementing1 = false;
			}
		}
		else {
			if (limbWaveAngle1 > 65.00) {
				limbWaveAngle1 -= 1.0;
			}
			if (limbWaveAngle1 <= 65.00) {
				limbWaveAngle1 = 65.00;
				limbWaveIncrementing1 = true;
			}
		}
		if (limbWaveIncrementing2) {
			if (limbWaveAngle2 < 125.00) {
				limbWaveAngle2 += 1.0;
			}
			if (limbWaveAngle2 >= 125.00) {
				limbWaveAngle2 = 125.00;
				limbWaveIncrementing2 = false;
			}
		}
		else {
			if (limbWaveAngle2 > 65.00) {
				limbWaveAngle2 -= 1.0;
			}
			if (limbWaveAngle2 <= 65.00) {
				limbWaveAngle2 = 65.00;
				limbWaveIncrementing2 = true;
			}
		}
	}

	// CAMERA MOVEMENT
	if (uptime > 8000 && uptime < 17000) {		// 7 seconds of zooming in
		if (elapsedTime >= 16) {
			sceneCam.Update('z');
		}
	}
	if (uptime > 16000 && uptime < 17000) {		// 1 second of pitching down
		if (elapsedTime >= 16) {
			sceneCam.Update('k');
		}
	}
	if (uptime > 19000 && uptime < 21000) {		// 2 seconds of pitching down
		if (elapsedTime >= 16) {
			sceneCam.Update('k');
		}
	}
	// MANUAL CONTROLS FOR THIS SCENE: 
	//	w to move up
	//	e to yaw right

	lastUpdateTime = currentTime;

	glutPostRedisplay();
}

void launchDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// draw the scene's objects starting here!!
	glPushMatrix();
	glTranslated(-10.0, 0.0, -10.0);

	// TEST SKY
	// draw the sky background first
	glColor3ub(255, 255, 255);
	drawSkybox();
	// END TEST SKY

	// draw the rest of the scene's objects starting here!!
	glPushMatrix();
	glTranslated(-10.0, 0.0, -10.0);
	drawBaseplate();
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	rebalancer.drawSquare();
	glPopMatrix();

	// SCENERY: LOCK!
	{
		glPushMatrix();
		glTranslated(-20.0, 0.0, -49.0);
		mountainRange();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-60.0, 0.0, 10.0);
		glPushMatrix();
		glRotated(90.0, 0.0, 1.0, 0.0);
		mountainRange();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(20.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(-15.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-35.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(26.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, -30.0);
		glPushMatrix();
		glRotated(101.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, 45.0);
		glPushMatrix();
		glRotated(120.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
	//glTranslated(-30.0, 5.0, -30.0);
	glTranslated(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, delta_Y, 0.0);
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//glTranslated(-30.0, 3.0, -30.0);
	glTranslated(0.0, -12.4 + delta_Y, 0.0);
	glPushMatrix();
	glRotated(angle, 0.0, 1.0, 0.0);
	glScaled(1.5, 1.5, 1.5);
	drawSpaceStation();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void launchIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	if (angle > 360.00) {
		angle = 0.00;
	}

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	if (uptime > 25000 && uptime < 28000) {
		delta_Y += 0.00;
		angle += 0.00;
	}
	else if (uptime > 28000 && uptime < 30000) {
		delta_Y += 0.05;
		angle += 0.02;
	}
	else if (uptime > 30000) {
		delta_Y += 0.08;
		angle += 0.05;
	}

	// CAMERA MOVEMENT
	if (uptime > 29000 && uptime < 33000) {	// 4 second of moving up
		if (elapsedTime >= 16) {
			sceneCam.Update('w');
		}
	}
	if (uptime > 33000 && uptime < 35000) { // 2 seconds of pitching up
		if (elapsedTime >= 16) {
			sceneCam.Update('i');
		}
	}
	if (uptime > 37000 && uptime < 38500) {
		if (elapsedTime >= 12) {
			sceneCam.Update('k');
		}
	}
	/*
		if (uptime > 16000 && uptime < 17000) {		// 1 second of pitching down
		if (elapsedTime >= 16) {
			sceneCam.Update('k');
		}
	}
	*/

	// MANUAL CONTROLS FOR THIS SCENE: 
	//	 not sure yet

	lastUpdateTime = currentTime;

	glutPostRedisplay();
}

void leavingEarthDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// TEST SKY
	// draw the sky background first
	glColor3ub(255, 255, 255);
	drawSkybox();
	// END TEST SKY

	glPushMatrix();
	glTranslated(12.0, 0.0, 12.0);

	// draw the scene's objects starting here!
	glPushMatrix();
	glTranslated(-13.0, 0.0, -13.0);
	//glTranslated(25.0, 25.0, 25.0);
	glPushMatrix();
	glRotated(-55.0 + angle * 3.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	earth.drawSphere(17.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// CLOCKTOWER AND SPACESTATION
	{
		glPushMatrix();

		glRotated(90.0, 1.0, 0.0, 0.0);
		glScaled(0.28, 0.28, 0.28);
		glTranslated(40.0, -230.0 + delta_Y, 40.0);
		glTranslated(0.0, 10.0, 10.0);

		glPushMatrix();
		glTranslated(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslated(0.0, /*delta_Y*/ 0.0, 0.0);
		glPushMatrix();
		glTranslated(0.0, 10.0 + delta_Z, 0.0);
		drawClockTower(engineOn);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glRotated(angle * 3.0, 0.0, 1.0, 0.0);
		glPushMatrix();
		glScaled(1.5, 1.5, 1.5);
		glPushMatrix();
		drawSpaceStation();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
	}

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void leavingEarthIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	// do whatever global coordinate parameter updates here
	angle += 0.02;
	if (angle > 360.0) {
		angle = 0.00;
	}

	if (uptime > 40000 && uptime < 55000) {
		delta_Y += 0.26;
	}
	if (uptime > 45000 && uptime < 55000) {
		delta_Y += 0.04;
		delta_Z += 0.12;
	}

	// then do whatever keyboard related movements here
	if (uptime > 40000 && uptime < 42000) {
		if (elapsedTime >= 16) {
			sceneCam.Update('e');
		}
	}
	lastUpdateTime = currentTime;

	glutPostRedisplay();
}

void onMoonDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glRotated(angle, 0.0, 1.0, 0.0);
	drawSkybox();
	glPopMatrix();

	glColor3ub(255, 255, 255);
	drawBaseplate();
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	rebalancer.drawSquare();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 53.0, 0.0);
		glPushMatrix();
		glTranslated(0.0, -delta_Y, 0.0);
			glPushMatrix();
			glScaled(2.0, 2.0, 2.0);
			//spaceship(angle * 15.0);
			drawClockTower(engineOn);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(35.0, 0.0, 0.0);
	{
		glPushMatrix();
		glTranslatef(16.0, 0.0, 0.0);
		glPushMatrix();
		glScaled(1.8, 1.8, 1.8);
		boyzMobile.draw();
		glPopMatrix();
		glPopMatrix();

		drawSkeletons();

		// ** drawing the flag object
		glPushMatrix();
		glTranslated(0.0, 2.0, 0.0);
		glRotated(-25.0, 0.0, 0.0, 1.0);
		drawFlagPole();
		glPopMatrix();
	}
	glPopMatrix();


	// LIGHTING
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	// light position
	GLfloat objectPosition[] = { 0.0, 5.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, objectPosition);
	// light properties
	GLfloat objectAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat objectDiffuse[] = { 4.0, 4.0, 4.0, 1.0 };
	GLfloat objectSpecular[] = { 4.0, 4.0, 4.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, objectAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, objectDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, objectSpecular);

	glFlush();
	glutSwapBuffers();
}
void onMoonIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;
	DWORD elapsedTime2 = currentTime - lastUpdateTime2;

	angle += 0.02;

	if (angle > 360.0) {
		angle = 0.00;
	}

	//SCENESTART 56000ms
	if (uptime > 56000 && uptime < 65000) {
		delta_Y += 0.10;
	}
	if (uptime > 63000 && uptime < 65000) {
		sceneCam.Update('z');
	}
	if (uptime > 66000 && uptime < 69000) {
		sceneCam.Update('e');
	}
	if (uptime > 71000 && uptime < 73000) {
		sceneCam.Update('i');
	}
	if (uptime > 65000 && uptime < 73000) {
		engineOn = 0;
	}

	glutPostRedisplay();
}

void leavingMoonDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHT2);
	GLfloat ambient[] = { 3.0, 3.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

	glColor3ub(255, 255, 255);
	drawSkybox();

	glDisable(GL_LIGHT2);

	glPushMatrix();
	glTranslated(25.0, 25.0, 25.0);
	glPushMatrix();
	glRotated(angle * 4.0, 1.0, 0.0, 0.0);
	moon.drawSphere(10.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(25.0, 25.0, 25.0);
	glPushMatrix();
	glScaled(0.10, 0.10, 0.10);
	glPushMatrix();
	glTranslated(2.0, -delta_Z, 2.0);
	glPushMatrix();
	glRotated(45.0, 0.0, 1.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(90.0, 1.0, 0.0, 0.0);
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glEnable(GL_LIGHT2);

	/* TEST SMALL POINT LIGHT */
	glDisable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	// light position
	GLfloat objectPosition[] = { 65.0, -8.0, 65.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, objectPosition);
	// light properties
	GLfloat objectAmbient[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat objectDiffuse[] = { 4.0, 4.0, 4.0, 1.0 };
	GLfloat objectSpecular[] = { 4.0, 4.0, 4.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, objectAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, objectDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, objectSpecular);

	glFlush();
	glutSwapBuffers();
}
void leavingMoonIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	angle += 0.02;
	delta_Z += 0.45;

	if (angle > 360.0) {
		angle = 0.00;
	}

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;
	DWORD elapsedTime2 = currentTime - lastUpdateTime2;

	std::cout << uptime << std::endl;

	// scenestart at 73000ms

	if (uptime > 73000 && uptime < 77000) {
		if (elapsedTime >= 16) {
			sceneCam.Update('i');
		}
	}
	if (uptime > 77000 && uptime < 78000) {
		if (elapsedTime >= 16) {
			sceneCam.Update('c');
		}
	}

	// MANUAL CONTROLS: L!

	glutPostRedisplay();
}

void spacePanoramaDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHT2);
	GLfloat ambient[] = { 3.0, 3.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

	drawSkybox();

	glDisable(GL_LIGHT2);

	glPushMatrix();
	glTranslated(1.0, 1.2, 1.0);
	solarSystem(angle);
	glPopMatrix();

	glPushMatrix();
	glTranslated(24.0, 1.5, 24.0);
	glPushMatrix();
	glScaled(0.05, 0.05, 0.05);
	glPushMatrix();
	glTranslated(delta_X, 0.0, delta_Y);
	glPushMatrix();
	glRotated(90.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-45.0, 0.0, 0.0, 1.0);
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	int angleInc = 5;
	for (int i = 0; i < 9; i++) {
		glPushMatrix();
		glRotated((40.0 * i), 0.0, 1.0, 0.0);
		asteroidBelt(3, angle);
		glPushMatrix();
		glTranslated(-1.0, 0.5, -1.0);
		asteroidBelt(2, angle * 2, 0.18);
		glPopMatrix();
		glPopMatrix();
	}

	glEnable(GL_LIGHT2);

	/* TEST SMALL POINT LIGHT */
	glDisable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	// light position
	GLfloat objectPosition[] = { 2.0, 0.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, objectPosition);
	// light properties
	GLfloat objectAmbient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat objectDiffuse[] = { 4.0, 4.0, 4.0, 1.0 };
	GLfloat objectSpecular[] = { 4.0, 4.0, 4.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, objectAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, objectDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, objectSpecular);

	glFlush();
	glutSwapBuffers();
}
void spacePanoramaIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;
	DWORD elapsedTime2 = currentTime - lastUpdateTime2;

	if (uptime > 86500 && uptime < 100000) {
		delta_X += 0.82;
		delta_Y += 0.82;
		angle += 0.02;

		if (angle > 360.00) {
			angle = 0.00;
		}
	}
	if (uptime > 86500 && uptime < 94000) {
		if (elapsedTime >= 12) {
			sceneCam.Update('c');
		}
	}
	if (uptime > 89500 && uptime < 90500) {
		if (elapsedTime >= 16) {
			sceneCam.Update('a');
		}
	}
	if (uptime > 90000 && uptime < 93000) {
		if (elapsedTime >= 12) {
			sceneCam.Update('a');
		}
	}
	if (uptime > 90000 && uptime < 96000) {
		if (elapsedTime >= 12) {
			sceneCam.Update('e');
		}
	}
	if (uptime > 96000 && uptime < 98000) {
		delta_X += 1.25;
		delta_Y += 1.25;
		if (elapsedTime > 12) {
			sceneCam.Update('z');
		}
	}
	lastUpdateTime = currentTime;

	glutPostRedisplay();
}

void atPlutoDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHT2);
	GLfloat ambient[] = { 3.0, 3.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

	// draw the scene's objects starting here!!
	glPushMatrix();
	glScaled(1.2, 1.2, 1.2);
	glColor3ub(255, 255, 255);
	drawSkybox();
	glPopMatrix();

	glDisable(GL_LIGHT2);

	// pluto
	glColor3ub(255, 255, 255);
	glPushMatrix();
	// glTranslated(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-40.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotated(angle, 0.0, 1.0, 1.0);
	pluto.drawSphere(15.0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// clocktower
	glPushMatrix();
	glTranslated(40.0 - delta_X, 0.0, 40.0 - delta_Z);
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(45.0, 0.0, 0.0, 1.0);
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();

	if (monsterIsOut) {
		glPushMatrix();
		glTranslated(2.0 + delta_Y, 0.0, 2.0 + delta_Y);
			glPushMatrix();
			glRotated(90.0, 1.0, 0.0, 0.0);
			glRotated(-45.0, 0.0, 0.0, 1.0);
			glRotated(-90.0, 0.0, 1.0, 0.0);
				glPushMatrix();
				monster.draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}
void atPlutoIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	// do whatever global coordinate parameter updates here
	angle += 0.02;
	if (angle > 360.00) {
		angle = 0.00;
	}

	// then do whatever keyboard related movements here
	if (uptime > 102000 && uptime < 103000) {
		if (elapsedTime >= 12) {
			sceneCam.Update('c');
			sceneCam.Update('c');
			sceneCam.Update('c');
			sceneCam.Update('c');
			sceneCam.Update('c');
		}
	}
	if (uptime > 103000 && uptime < 107000) {
		delta_X += 0.06;
		delta_Z += 0.06;
		if (elapsedTime >= 12) {
			sceneCam.Update('d');
		}
	}
	if (uptime > 107000) {
		monsterIsOut = true;
	}
	if (uptime > 107000 && uptime < 108000) {
		delta_Y += 0.20;
		delta_X += 0.06;
		delta_Z += 0.06;
	}
	if (uptime > 105000 && uptime < 106000) {
		sceneCam.Update('q');
	}
	if (uptime > 108000) {
		if (uptime > 108000 && uptime < 108800) {
			delta_Y = 11.8 + 0.3 * sin(angle * 40.0);
			std::cout << delta_Y << std::endl;
		}
		if (uptime > 108800 && uptime < 109600) {
			delta_Y = 11.8 + 0.1 * sin(angle * 40.0);
			std::cout << delta_Y << std::endl;
		}
		if (uptime > 109600) {
			delta_Y = 11.8;
		}
		delta_X -= 0.35;
		delta_Z -= 0.35;
		engineOn = 0;
	}
	if (uptime > 109600 && uptime < 110600) {
		if (elapsedTime >= 12) {
			sceneCam.Update('q');
			sceneCam.Update('q');
			sceneCam.Update('q');
		}
	}

	glutPostRedisplay();
}

void backAtEarthDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHT2);
	GLfloat ambient[] = { 3.0, 3.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

	// skybox
	drawSkybox();

	glDisable(GL_LIGHT2);

	glPushMatrix();
	glTranslated(0.0, -3.0, 0.0);

	// draw the scene's objects starting here!!
	glPushMatrix();
	glTranslated(-40.0, 0.0, -40.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-83.0 - angle * 2.8, 0.0, 0.0, 1.0);
	earth.drawSphere(12.0);
	glPopMatrix();
	glPopMatrix();

	// clocktower
	glPushMatrix();
	glTranslated(22.0 - delta_X, 1.2 + delta_Y * 0.05, 22.0 - delta_Z);
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(45.0, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScaled(0.10, 0.10, 0.10);
	glRotated(180.0, 1.0, 0.0, 0.0);
	{
		glRotated(angle * 10.0, 0.0, 1.0, 0.0);
		glRotated(angle * 20.0, 0.0, 0.0, 1.0);
	}
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void backAtEarthIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	angle += 0.02;
	if (angle > 360.00) {
		angle = 0.00;
	}

	if (uptime > 114500 && uptime < 121300) {
		delta_X += 0.14;
		delta_Z += 0.14;
		delta_Y += 0.01;
	}
	if (uptime > 114500 && uptime < 121300) {
		if (elapsedTime >= 16) {
			sceneCam.Update('z');
			sceneCam.Update('z');
		}
	}

	glutPostRedisplay();
}

void mountainDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

	glEnable(GL_LIGHT3);
	GLfloat light_position[] = { 10.0, 20.0, 0.0, 0.0 };	// Light position (from top)
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };       // Dimmer diffuse light color
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };       // Dimmer ambient light color
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };      // Specular light color

	glLightfv(GL_LIGHT3, GL_POSITION, light_position);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);

	// TEST SKY
	glColor3ub(255, 255, 255);
	drawSkybox();
	// DRAW TEST SKY

	glPushMatrix();
	glTranslated(0.0, -4.0, 0.0);

	// BASEPLATE
	glPushMatrix();
	glTranslated(-10.0, 0.0, -10.0);
	drawBaseplate();
	glPopMatrix();
	// REBALANCER
	glPushMatrix();
	glTranslated(0.0, -10.0, 0.0);
	rebalancer.drawSquare();
	glPopMatrix();

	// SCENERY: LOCK!
	{
		glPushMatrix();
		glTranslated(-20.0, 0.0, -49.0);
		mountainRange();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-60.0, 0.0, 10.0);
		glPushMatrix();
		glRotated(90.0, 0.0, 1.0, 0.0);
		mountainRange();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(20.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(-15.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-35.0, 0.0, 20.0);
		glPushMatrix();
		glRotated(26.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, -30.0);
		glPushMatrix();
		glRotated(101.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, 45.0);
		glPushMatrix();
		glRotated(120.0, 0.0, 1.0, 0.0);
		forest();
		glPopMatrix();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslated(0.0, delta_Y - 3.0, 0.0);
	glPushMatrix();
	glRotated(-delta_Z, 0.0, 0.0, 1.0);
	drawClockTower(engineOn);
	glPopMatrix();
	glPopMatrix();

	// BOYZMOBILE AND RKRL SQUARE
	{
		glPushMatrix();
		glTranslated(40.0 + delta_X, 25.0, 0.0);

		glPushMatrix();
		glRotated(90.0, 0.0, 1.0, 0.0);
		boyzMobile_alt.draw();
		glPopMatrix();
		glPushMatrix();
		glRotated(90.0, 1.0, 0.0, 0.0);
		glTranslated(13.5, 0.3, -3.0);
			glPushMatrix();
			glScaled(4.5, 1.0, 3.0);
			rickrollSquare.drawSquare();
			glPopMatrix();
		glPopMatrix();

		glPopMatrix();
	}

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void mountainIdle() {
	DWORD start = GetTickCount64();

	while (GetTickCount64() - start < 1000 / FPS);

	DWORD currentTime = GetTickCount64();
	DWORD uptime = currentTime - programStart;
	DWORD elapsedTime = currentTime - lastUpdateTime;

	// do whatever global coordinate parameter updates here
	delta_X -= 0.20;

	if (uptime > 120000 && uptime < 122600) {
		delta_Y -= 0.38;
	}
	if (uptime > 122600 && uptime < 150000) {
		delta_Z = -25.0;
	}
	// then do whatever keyboard related movements here
	if (uptime > 125500 && uptime < 126600) {
		if (elapsedTime >= 16) {
			sceneCam.Update('w');
			sceneCam.Update('w');
			sceneCam.Update('w');
			sceneCam.Update('i');
		}
	}
	if (uptime > 129500 && uptime < 135000) {
		if (elapsedTime >= 16) {
			sceneCam.Update('i');
		}
	}

	// RICKROLL UPDATES HERE
	{
		if (elapsedTime >= 160) {
			rickrollSquare.text.~Texture();
			if (currentImageIndex < 10 && !decrementing) {
				currentImageIndex++;
				if (currentImageIndex == 10) {
					decrementing = true;
				}
			}
			else if (currentImageIndex > 0 && decrementing) {
				currentImageIndex--;
				if (currentImageIndex == 0) {
					decrementing = false;
				}
			}
			else if (currentImageIndex == 0 && !decrementing) {
				currentImageIndex = 10;
				decrementing = true;
			}
			else if (currentImageIndex == 10 && decrementing) {
				currentImageIndex = 0;
				decrementing = false;
			}
			std::cout << currentImageIndex << std::endl;
			lastUpdateTime = currentTime;
			rickrollSquare.rr_set(2.0, currentImageIndex);
			/*

			*/
			// ATTEMPT: FREE EXISTING MEMORY
			// rickrollSquare.text.~Texture();
			// lastUpdateTime = currentTime;
			// rickrollSquare.rr_set(2.0, rickrollSquare.nextRickrollImage());
		}
	}


	glutPostRedisplay();
}

// =================== SCENES ========================= //