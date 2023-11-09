#ifndef _VECTOR_INCLUDE
#define _VECTOR_INCLUDE

class Point3D;

class Vector3D
{
public:
	double x, y, z;

	Vector3D() {
		x = 0;
		y = 0;
		z = 0;
	};
	Vector3D(double xx, double yy, double zz);
	Vector3D(Point3D a, Point3D b);
	void set(double xx, double yy, double zz);
	double Length();
	Vector3D Add(Vector3D v);
	Vector3D Scale(double s);
	Vector3D Unit();
	double DotProduct(Vector3D v);
	double AngleBetween(Vector3D v);
	Vector3D CrossProduct(Vector3D v);
};

#endif