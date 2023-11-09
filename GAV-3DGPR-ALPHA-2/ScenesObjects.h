#include <Windows.h>
#include <stdlib.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>

#include "Point3D.h"
#include "Vector3D.h"
#include "Texture.h"
#include "TexturedShape3D.h"
#include "BlenderMesh.h"
#include "DannyObjects.h"

#define PI          3.1415926535897932384626433832795

// blender meshes
blModel boyzMobile, boyzMobile_alt;
blModel cube;
blModel skeletons;
blModel clockTowerShip_body, clockTowerShip_engine, clockTowerShip_dome, clockTowerShip_plume;
blModel asteroid;
blModel sst_edgepillar, sst_core_bottom, sst_core_top, sst_roads, sst_roadmarks;
blModel monster;

// non-blender meshes
TexturedShape skybox;
TexturedShape baseplate;
TexturedShape rebalancer;
TexturedShape flag;     // ** the object used for the textured flag
TexturedShape sun, mercury, venus, earth, moon;
TexturedShape mars, jupiter, saturn, uranus, neptune;
TexturedShape pluto;
TexturedShape saturnRings;
TexturedShape rickrollSquare;

// Define flag dimensions
const float flagWidth = 2.5f;
const float flagHeight = 1.5f;
const float poleHeight = 8.0f;

// load in your blender meshes by calling the load() function and .obj file name
void initBlenderMeshes() {
    asteroid.load("asteroid.obj");
    boyzMobile.load("boyzMobile-FINAL.obj");
    boyzMobile_alt.load("boyzMobile-ALTERNATE.obj");
    cube.load("cube.obj");
    skeletons.load("skeleton-FINAL.obj");
    clockTowerShip_body.load("clocktower-body.obj");
    clockTowerShip_engine.load("clocktower-engine.obj");
    clockTowerShip_dome.load("clocktower-dome.obj");
    clockTowerShip_plume.load("clocktower-plume.obj");
    sst_edgepillar.load("sst-EDGEPILLAR.obj");
    sst_core_top.load("sst-CORE-TOP.obj");
    sst_core_bottom.load("sst-CORE-BOTTOM.obj");
    sst_roads.load("sst-ROADS.obj");
    sst_roadmarks.load("sst-ROADMARKS.obj");
    monster.load("space-monster-source.obj");
}

void initSceneOneTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    baseplate.set(2.0, (char*)"grass.bmp");
    rebalancer.set(1.0, (char*)"white-rebalancer.bmp");
}

void initLeavingEarthTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    earth.set(2.0, (char*)"earth.bmp");
}

void initSpacePanoramaTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    sun.set(2.0, (char*)"sunSurface.bmp");
    mercury.set(2.0, (char*)"mercury.bmp");
    venus.set(2.0, (char*)"venus.bmp");
    earth.set(2.0, (char*)"earth.bmp");
    moon.set(2.0, (char*)"moon.bmp");
    mars.set(2.0, (char*)"mars.bmp");
    jupiter.set(2.0, (char*)"jupiter.bmp");
    saturn.set(2.0, (char*)"saturn.bmp");
    saturnRings.set(2.0, (char*)"saturnRings.bmp");
    uranus.set(2.0, (char*)"uranus.bmp");
    neptune.set(2.0, (char*)"neptune.bmp");
    pluto.set(2.0, (char*)"pluto.bmp");
}

void initAtPlutoTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    pluto.set(2.0, (char*)"pluto.bmp");
    earth.set(2.0, (char*)"earth.bmp");
}

void initOnMoonTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    baseplate.set(2.0, (char*)"moonSurface.bmp");
    flag.set(2.0, (char*)"umsflag-yellowbg.bmp");
}

void initLeavingMoonTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    moon.set(2.0, (char*)"moon.bmp");
}

void initBackAtEarthTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    earth.set(2.0, (char*)"earth.bmp");
}

void initMountainTextures() {
    Textures_Initialise();
    skybox.set(2.0, (char*)"nightSky.bmp");
    baseplate.set(2.0, (char*)"grass.bmp");
    rebalancer.set(1.0, (char*)"white-rebalancer.bmp");
    rickrollSquare.set(2.0, (char*)"rickroll-0.bmp");
}

void drawSkybox() {

    glPushMatrix();

    glScaled(50.0, 50.0, 50.0);

    glPushMatrix();
    glTranslated(0.0, -2.0, 0.0);
    skybox.drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 2.0, 0.0);
    skybox.drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, -2.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    skybox.drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, 2.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    skybox.drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.0, 0.0, 0.0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    skybox.drawSquare();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.0, 0.0, 0.0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    skybox.drawSquare();
    glPopMatrix();

    glPopMatrix();
}

void drawBaseplate() {
    glPushMatrix();
    glTranslated(0.0, 0.0, 0.0);
    glPushMatrix();
    glScaled(75.0, 1.0, 75.0);
    baseplate.drawSquare();
    glPopMatrix();
    glPopMatrix();
}

void mountain(int plus_X, int plus_Y, float base, float height) {
    glPushMatrix();
    glRotated(270.0, 1.0, 0.0, 0.0);
    glTranslated(plus_X, plus_Y, 0.0);
    glColor3ub(144, 123, 90);
    glutSolidCone(base, height, 50, 50);
    glPopMatrix();
}

void mountainRange() {
    // front group
    mountain(35, 2, 12.0, 16.0);
    mountain(16, 1, 12.0, 15.0);
    mountain(-30, 1, 13.0, 17.0);
    mountain(8, 3, 15.0, 19.0);
    mountain(-10, 0, 11.0, 16.0);
    mountain(-5, 0, 12.5, 16.0);
    mountain(-25, -1, 12.0, 15.0);
    mountain(15, 0, 13.0, 16.0);
    mountain(24, 0, 13.0, 17.0);
    mountain(29, 1, 12.5, 16.0);
    mountain(-40, 1, 13.5, 17.0);
    mountain(-50, 0, 12.0, 18.0);
    mountain(-55, -15, 14.0, 19.0);
    mountain(-58, -24, 14.5, 17.0);
    mountain(-59, -35, 14.5, 16.0);
}

void drawMoon() {
    glPushMatrix();
    glColor3ub(255.0, 255.0, 255.0);
    moon.drawSphere(5.0);
    glPopMatrix();
}

void drawFlagPole() {
    // ** flag pole and umsflag combined into one function

    // flag pole portion
    glPushMatrix();
    glTranslatef(-1.25, -2.5, 0.0);
    glColor3ub(100.0, 40.0, 6.0);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // Set pole color (gray)
    glVertex3f(-0.1f, 0.0f, -0.1f);
    glVertex3f(-0.1f, poleHeight, -0.1f);
    glVertex3f(0.1f, poleHeight, -0.1f);
    glVertex3f(0.1f, 0.0f, -0.1f);

    glVertex3f(0.1f, 0.0f, -0.1f);
    glVertex3f(0.1f, poleHeight, -0.1f);
    glVertex3f(0.1f, poleHeight, 0.1f);
    glVertex3f(0.1f, 0.0f, 0.1f);

    glVertex3f(0.1f, 0.0f, 0.1f);
    glVertex3f(0.1f, poleHeight, 0.1f);
    glVertex3f(-0.1f, poleHeight, 0.1f);
    glVertex3f(-0.1f, 0.0f, 0.1f);

    glVertex3f(-0.1f, 0.0f, 0.1f);
    glVertex3f(-0.1f, poleHeight, 0.1f);
    glVertex3f(-0.1f, poleHeight, -0.1f);
    glVertex3f(-0.1f, 0.0f, -0.1f);
    glEnd();

    glPopMatrix();

    // textured flag portion
    // ** using the TexturedShape class to draw this portion. the TexturedShape class allows for textured shapes
    glPushMatrix();
    glRotated(90.0, 1.0, 0.0, 0.0);
    glTranslated(0.7, 0.0, -4.3);
    glScaled(1.0, 0.55, 0.55);
    glColor3ub(255.0, 255.0, 255.0);
    flag.drawSquare();
    glPopMatrix();
}

void tree(int no_cones, float cyl_ht_coeff, float x, float z) {
    glPushMatrix();
    glTranslated(x, 0.0, z);
    {
        int numSlices = 50;     // number of slices used to draw the cylinder and cones
        int numCones = no_cones;       // number of cones stacked on top of the cylinder
        float cylinderRadius = 0.175f;
        float cylinderHeight = cyl_ht_coeff * 1.0f;
        float coneRadius = 0.5f;
        float coneHeight = 0.9f;
        float coneSpacing = 0.325f;

        // draw cylinder (trunk)
        float sliceAngle = (2 * PI) / numSlices;

        glColor3f(0.25f, 0.0f, 0.0f);

        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= numSlices; i++) {
            float angle = i * sliceAngle;
            float x = cylinderRadius * cos(angle);
            float z = cylinderRadius * sin(angle);
            glVertex3f(x, cylinderHeight, z);
            glVertex3f(x, 0.0f, z);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);  // Bottom center point
        for (int i = 0; i <= numSlices; i++) {
            float angle = i * sliceAngle;
            float x = cylinderRadius * cos(angle);
            float z = cylinderRadius * sin(angle);
            glVertex3f(x, 0.0f, z);
        }
        glEnd();

        // draw cones
        float coneOffset = coneHeight * 1.0f;
        for (int i = 0; i < numCones; i++) {
            float coneY = coneOffset + i * (coneSpacing);
            glColor3f(0.0f, 0.25f, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, coneY + coneHeight * 0.5f, 0.0f);
            for (int j = 0; j <= numSlices; j++) {
                float angle = j * sliceAngle;
                float x = coneRadius * cos(angle);
                float z = coneRadius * sin(angle);
                glVertex3f(x, coneY, z);
            }
            glEnd();
        }
    }
    glPopMatrix();
}

void forest() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j += 4) {
            tree(5, 1.3, j, (20 - (i * 5)));
        }
    }
}

void solarSystem(float angle = 0.00) {
    // core star
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glRotated(angle * 5.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(90, 1.0, 0.0, 0.0);
    glEnable(GL_LIGHT2);
    sun.drawSphere(4.0);
    glDisable(GL_LIGHT2);
    glPopMatrix();
    glPopMatrix();

    // MERCURY
    glPushMatrix();
    glRotated(2.0 + angle * 3.0, 0.0, 1.0, 0.0);		// determines orbital speed about the core
    glPushMatrix();
    glTranslatef(10.0, 0.0, 10.0);				// determines orbital radius about core
//glRotated(angle * 80.0, 0.0, 1.0, 0.0);	// determines planet rotation, if not otherwise 'tidally locked'
    mercury.drawSphere(0.3);
    glPopMatrix();
    glPopMatrix();

    // VENUS
    glPushMatrix();
    glRotated(-2.0 + angle * 2.5, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(13.0, 0.0, 13.0);
    glRotated(angle * 20.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(90.0, 1.0, 0.0, 0.0);
    venus.drawSphere(0.5);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // EARTH
    glPushMatrix();
    glRotated(-0.5 + angle * 2.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(22.0, 0.0, 22.0);
    glRotated(angle * 20.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glRotated(180.0, 0.0, 1.0, 0.0);
    earth.drawSphere(0.55);
    glPopMatrix();
    glPushMatrix();
    glRotated(-1.0 + angle * 1.0, 0.0, 1.0, 0.0);
    glTranslatef(0.8, 0.0, 0.8);
    moon.drawSphere(0.15);
    glPopMatrix();
    // END MOON
    glPopMatrix();
    glPopMatrix();

    // MARS
    glPushMatrix();
    glRotated(2.0 + angle * 1.8, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(27.0, 0.0, 27.0);
    glRotated(angle * 18.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    mars.drawSphere(0.35);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // JUPITER
    glPushMatrix();
    glRotated(-7.5 + angle * 0.8, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(33.0, 0.0, 33.0);
    glRotated(angle * 5.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    jupiter.drawSphere(1.5);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // SATURN
    glPushMatrix();
    glRotated(-6.0 + angle * 0.6, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(39.0, 0.0, 39.0);
    glRotated(angle * 3.5, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    saturn.drawSphere(1.1);
    glPopMatrix();
    glPushMatrix();
    glRotated(90.0, 0.0, 1.0, 0.0);
    saturnRings.drawCircle(2.4);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // URANUS
    glPushMatrix();
    glRotated(60.0 + angle * 0.4, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(43.0, 0.0, 43.0);
    glRotated(angle * 3.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    uranus.drawSphere(1.0);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // NEPTUNE
    glPushMatrix();
    glRotated(120.0 + angle * 0.2, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(46.0, 0.0, 46.0);
    glRotated(angle * 2.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(-90.0, 1.0, 0.0, 0.0);
    neptune.drawSphere(1.01);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // PLUTO
    glPushMatrix();
    glPushMatrix();
    glTranslatef(90.0, 0.0, 90.0);
    glRotated(angle * 3.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(90.0, 0.0, 1.0, 0.0);
    pluto.drawSphere(2.0);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawBoyzMobile() {
    boyzMobile.draw();
}

void drawSkeletons() {
    skeletons.draw();
}

void drawClockTower(int plumeOn = 0) {
    clockTowerShip_body.draw();
    clockTowerShip_dome.draw();
    clockTowerShip_engine.draw();
    if (plumeOn == 1) {
        clockTowerShip_plume.draw();
    }
}

void asteroidBelt(int modulo, float angle = 0.00, float scaleFactor = 0.25) {
    glPushMatrix();
    glRotated(angle, 0.0, 1.0, 0.0);
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glRotated((0.0 + (i * 5.0)), 0.0, 1.0, 0.0);
        glPushMatrix();
        glTranslated(30.0, (i % modulo), 30.0);
        glPushMatrix();
        glScaled(scaleFactor, scaleFactor, scaleFactor);
        glRotated(angle * 10.0, 0.0, 1.0, 0.0);
        asteroid.draw();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();
}

void drawSpaceStation() {
    // CORE
    sst_core_top.draw();
    sst_core_bottom.draw();
    // EDGEPILLARS
    sst_edgepillar.draw();
    // ROADS
    sst_roads.draw();
    sst_roadmarks.draw();
}