// supposedly, this header file will cover all types of textured 3D objects
// this currently includes spheres, cylinders (and cones, since you make cones with cylinders too in this case), and cubes/cuboids

#ifndef TEXTUREDSHAPE_H
#define TEXTUREDSHAPE_H

class Vector3D;
class Texture;

class TexturedShape
{
public:
	double radius;
	Vector3D norm;
	Texture text;
	char* rickrollTexturePaths[11];

	TexturedShape() {};
	~TexturedShape() {};

	void set(double r, char* file);
	void drawSphere(float radius);
	void drawCylinder(float radius, float height);
	void drawCone(float base, float top, float height);
	void drawSquare();
	void drawCircle(float radius);
	void loadRickrollSet();
	void rr_set(double r, int index);

	// EXPERIMENT: PNG IMAGE
	void set_png();

	// void toggleLight();
};

#endif