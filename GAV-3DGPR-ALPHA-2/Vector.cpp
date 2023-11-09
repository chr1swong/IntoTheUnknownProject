#include "Point3D.h"
#include "Vector3D.h"	
#include <math.h>
#include <windows.h>
#include <gl\GL.h>


Vector3D::Vector3D(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}

void Vector3D::set(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
}

Vector3D::Vector3D(Point3D head, Point3D tail) {
	x = head.x - tail.x;
	y = head.y - tail.y;
	z = head.z - tail.z;
}

double Vector3D::Length() {
	return sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::Add(Vector3D v) {
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::Scale(double s) {
	return Vector3D(x * s, y * s, z * s);
}

Vector3D Vector3D::Unit() {
	Vector3D V = Vector3D(x, y, z);
	V = V.Scale(1.0 / V.Length());
	return V;
}

double Vector3D::DotProduct(Vector3D v) {
	return x * v.x + y * v.y + z * v.z;
}

double Vector3D::AngleBetween(Vector3D v) {
	double l1 = this->Length();
	double l2 = v.Length();
	double dot = this->DotProduct(v);
	dot = dot / (l1 * l2);
	double angle = acos(dot);
	return angle;
}

Vector3D Vector3D::CrossProduct(Vector3D v) {
	double detA = y * v.z - z * v.y;
	double detB = -(x * v.z - z * v.x);
	double detC = x * v.y - y * v.x;
	return Vector3D(detA, detB, detC);
}