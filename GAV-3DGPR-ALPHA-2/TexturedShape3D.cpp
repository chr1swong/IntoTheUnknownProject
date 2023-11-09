#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>

#include "Vector3D.h"
#include "Texture.h"
#include "TexturedShape3D.h"

#define PI				3.1415926535897932384626433832795

// set the object's texture
void TexturedShape::set(double r, char* file) {
	radius = r;
	text.Initialise(file);
	norm.set(0.0, 1.0, 0.0);
}

// draw 3D sphere
void TexturedShape::drawSphere(float radius) {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBindTexture(GL_TEXTURE_2D, text.ID);

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	gluSphere(sphere, radius, 100, 100);

	glBindTexture(GL_TEXTURE_2D, 0);

	gluDeleteQuadric(sphere);
}

// draw 3D cylinder (in this case base = top)
void TexturedShape::drawCylinder(float radius, float height) {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBindTexture(GL_TEXTURE_2D, text.ID);

	GLUquadricObj* cylinder = NULL;

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);

	gluCylinder(cylinder, radius, radius, height, 50, 50);

	glBindTexture(GL_TEXTURE_2D, 0);

	gluDeleteQuadric(cylinder);
}

// draw cone (more specifically frustum)
void TexturedShape::drawCone(float base, float top, float height) {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBindTexture(GL_TEXTURE_2D, text.ID);

	GLUquadricObj* cylinder = NULL;

	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);

	gluCylinder(cylinder, base, top, height, 50, 50);

	glBindTexture(GL_TEXTURE_2D, 0);

	gluDeleteQuadric(cylinder);
}

// draw flat square (sort-of like a 2D plane)
void TexturedShape::drawSquare() {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBindTexture(GL_TEXTURE_2D, text.ID);
	glBegin(GL_QUADS);
	glNormal3d(norm.x, norm.y, norm.z);
	glTexCoord2f(1.0, 1.0);
	glVertex3d(radius, 0.0, radius);
	glTexCoord2f(1.0, 0.0);
	glVertex3d(radius, 0.0, -radius);
	glTexCoord2f(0.0, 0.0);
	glVertex3d(-radius, 0.0, -radius);
	glTexCoord2f(0.0, 1.0);
	glVertex3d(-radius, 0.0, radius);

	glEnd();
}

// draw flat circle (sort-of like a 2D disk)
void TexturedShape::drawCircle(float radius) {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);

	glBindTexture(GL_TEXTURE_2D, text.ID);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(norm.x, norm.y, norm.z);
	glTexCoord2f(0.5, 0.5f);
	glVertex3d(0.0, 0.0, 0.0);

	int numSegments = 360;
	double angleIncrement = 2.0 * PI / numSegments;

	for (int i = 0; i <= numSegments; i++) {
		double angle = i * angleIncrement;
		double x = radius * cos(angle);
		double z = radius * sin(angle);
		glTexCoord2f((x + radius) / (2.0 * radius), (z + radius) / (2.0 * radius));
		glVertex3d(x, 0.0, z);
	}

	glEnd();
}

void TexturedShape::loadRickrollSet() {
	Textures_Initialise();
	rickrollTexturePaths[0] = (char*)"rickroll-0.bmp";
	rickrollTexturePaths[1] = (char*)"rickroll-1.bmp";
	rickrollTexturePaths[2] = (char*)"rickroll-2.bmp";
	rickrollTexturePaths[3] = (char*)"rickroll-3.bmp";
	rickrollTexturePaths[4] = (char*)"rickroll-4.bmp";
	rickrollTexturePaths[5] = (char*)"rickroll-5.bmp";
	rickrollTexturePaths[6] = (char*)"rickroll-6.bmp";
	rickrollTexturePaths[7] = (char*)"rickroll-7.bmp";
	rickrollTexturePaths[8] = (char*)"rickroll-8.bmp";
	rickrollTexturePaths[9] = (char*)"rickroll-9.bmp";
	rickrollTexturePaths[10] = (char*)"rickroll-10.bmp";
}

void TexturedShape::rr_set(double r, int index) {
	radius = r;
	text.Initialise(rickrollTexturePaths[index]);
	norm.set(0.0, 1.0, 0.0);
}

void TexturedShape::set_png() {
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);


}

/*
void TexturedShape::loadPlume() {
	Textures_Initialise();
	plumeTexturePaths[0] = (char*)"flame1-bitmap.bmp";
	plumeTexturePaths[1] = (char*)"flame2-bitmap.bmp";
}

void TexturedShape::plume_set(double r, int index) {
	radius = r;
	text.Initialise(plumeTexturePaths[index]);
	norm.set(0.0, 1.0, 0.0);
}
*/
