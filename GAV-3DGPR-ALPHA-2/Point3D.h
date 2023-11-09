#ifndef _POINT_INCLUDE
#define _POINT_INCLUDE

class Vector3D;

class Point3D
{
public:
	double x, y, z;

	Point3D() {
		x = 0;
		y = 0;
		z = 0;
	};
	Point3D(double xx, double yy, double zz);
	void set(double xx, double yy, double zz);
	Point3D AddVector(Vector3D v);
};

#endif