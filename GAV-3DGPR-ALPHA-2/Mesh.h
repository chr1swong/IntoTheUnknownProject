#ifndef MESH_H
#define MESH_H

class Point3D;
class Vector3D;
class Texture;

class Face {
public:
	int nVerts;
	int* verts;
	int textID;
	Point3D* textUV;

	Face() {};
};

class Mesh {
public:
	int nVerts;
	int nFaces;
	int nTexts;
	Point3D* verts;
	Vector3D* norms;
	Face* faces;
	Texture* textures;

	Mesh() {};
	~Mesh();
	void Load(char* filename);
	void Draw();
};



#endif