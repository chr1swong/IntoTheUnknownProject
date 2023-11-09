#include "Vector3D.h"
#include "Point3D.h"
#include "Texture.h"
#include "mesh.h"
#include <Windows.h>
#include <gl\GL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Mesh::Load(char* filename) {

	FILE* file;
	char line[100];
	fopen_s(&file, filename, "r");

	if (file != NULL) {
		// get nTextures
		fgets(line, 100, file);
		nTexts = atoi(line);
		textures = new Texture[nTexts];
		for (int i = 0; i < nTexts; i++) {
			fgets(line, 100, file);
			int n = strlen(line);
			line[n - 1] = '\0';
			textures[i].Initialise(line);
		}
		// get nVerts
		fgets(line, 100, file);
		nVerts = atoi(line);
		verts = new Point3D[nVerts];
		for (int i = 0; i < nVerts; i++) {
			fgets(line, 100, file);
			double x, y, z;
			char* tok;
			char* next;
			tok = strtok_s(line, " \\n", &next);
			x = atof(tok);
			tok = strtok_s(NULL, " \\n", &next);
			y = atof(tok);
			tok = strtok_s(NULL, " \\n", &next);
			z = atof(tok);
			verts[i].x = x;
			verts[i].y = y;
			verts[i].z = z;
		}
		// get nFaces
		fgets(line, 100, file);
		nFaces = atoi(line);
		faces = new Face[nFaces];
		norms = new Vector3D[nFaces];
		for (int i = 0; i < nFaces; i++) {
			int n = atoi(fgets(line, 100, file));
			faces[i].nVerts = n;
			faces[i].verts = new int[n];
			faces[i].textUV = new Point3D[n];
			fgets(line, 100, file);
			char* next;
			char* tok = strtok_s(line, " \\n", &next);
			faces[i].verts[0] = atoi(tok);
			for (int j = 1; j < n; j++) {
				tok = strtok_s(NULL, " \\n", &next);
				faces[i].verts[j] = atoi(tok);
			}
			faces[i].textID = atoi(fgets(line, 100, file));
			fgets(line, 100, file);
			faces[i].textUV[0].x = atoi(strtok_s(line, " \\n", &next));
			faces[i].textUV[0].y = atoi(strtok_s(NULL, " \\n", &next));
			for (int j = 1; j < n; j++) {
				faces[i].textUV[j].x = atoi(strtok_s(NULL, " \\n", &next));
				faces[i].textUV[j].y = atoi(strtok_s(NULL, " \\n", &next));
			}
		}
	}
	fclose(file);

	for (int i = 0; i < nFaces; i++) {
		Point3D a = verts[faces[i].verts[0]];
		Point3D b = verts[faces[i].verts[1]];
		Point3D c = verts[faces[i].verts[2]];
		Vector3D v1(b, a);
		Vector3D v2(c, b);
		Vector3D cross = v1.CrossProduct(v2);
		cross = cross.Unit();
		norms[i] = cross;
	}

}

void Mesh::Draw() {
	double x, y, z, u, v;

	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, col);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, col);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, col);

	for (int i = 0; i < nFaces; i++) {
		glBindTexture(GL_TEXTURE_2D, textures[faces[i].textID].ID);
		glBegin(GL_POLYGON);
		glNormal3d(norms[i].x, norms[i].y, norms[i].z);
		for (int j = 0; j < faces[i].nVerts; j++) {
			u = faces[i].textUV[j].x;
			v = faces[i].textUV[j].y;
			x = verts[faces[i].verts[j]].x;
			y = verts[faces[i].verts[j]].y;
			z = verts[faces[i].verts[j]].z;
			glTexCoord2f(u, v);
			glVertex3d(x, y, z);
		}
		glEnd();
	}
}

Mesh::~Mesh() {
	if (verts) {
		delete verts;
	}
	if (faces) {
		for (int i = 0; i < nFaces; i++) {
			delete faces[i].verts;
		}
		delete faces;
	}
}