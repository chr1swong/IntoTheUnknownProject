#include "Point3D.h"
#include "Vector3D.h"

Point3D::Point3D(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}

void Point3D::set(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}

Point3D Point3D::AddVector(Vector3D v) {
	return Point3D(x + v.x, y + v.y, z + v.z);
}