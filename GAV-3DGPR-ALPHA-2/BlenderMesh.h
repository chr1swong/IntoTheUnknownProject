#ifndef BLENDERMESH_H
#define BLENDERMESH_H

#include <Windows.h>
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <string>

class blModel {
private:
	class Face {
	public:
		int edge;
		int* vertices;
		int* texcoords;
		int normal;

		Face(int edge, int* vertices, int* texcoords, int normal = -1) {
			this->edge = edge;
			this->vertices = vertices;
			this->texcoords = texcoords;
			this->normal = normal;
		}
	};

	std::vector<float*> vertices;
	std::vector<float*> texcoords;
	std::vector<float*> normals;
	std::vector<Face> faces;
	std::vector<float*> colors;
	GLuint list;

public:
	void load(const char* filename) {
		std::string line;
		std::vector<std::string> lines;
		std::ifstream in(filename);
		if (!in.is_open()) {
			printf("Cannot load model %s\n", filename);
			return;
		}
		while (!in.eof()) {
			std::getline(in, line);
			lines.push_back(line);
		}
		in.close();
		float a, b, c;
		float red, green, blue;	// new variables for color values
		for (std::string& line : lines) {
			if (line[0] == 'v') {
				if (line[1] == ' ') {
					sscanf_s(line.c_str(), "v %f %f %f", &a, &b, &c);
					vertices.push_back(new float[3]{ a, b, c });
				}
				else if (line[1] == 't') {
					sscanf_s(line.c_str(), "vt %f %f", &a, &b);
					texcoords.push_back(new float[2]{ a, b });
				}
				else if (line[1] == 'n') {
					sscanf_s(line.c_str(), "vn %f %f %f", &a, &b, &c);
					normals.push_back(new float[3]{ a, b, c });
				}
				else if (line[1] == 'c') {	// new case for color values
					sscanf_s(line.c_str(), "vc %f %f %f", &red, &green, &blue);
					colors.push_back(new float[3]{ (red / 255), (green / 255), (blue / 255) });
				}
			}
			else if (line[0] == 'f') {
				int v0, v1, v2, v3, t0, t1, t2, t3, n;
				if (count(line.begin(), line.end(), ' ') == 4) {
					sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n, &v3, &t3, &n);
					int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
					int* v_sec = new int[3]{ v2 - 1, v3 - 1, v0 - 1 };
					faces.push_back(Face(3, v, NULL, n - 1));
					faces.push_back(Face(3, v_sec, NULL, n - 1));
				}
				else {
					sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
					int* v = new int[3]{ v0 - 1, v1 - 1, v2 - 1 };
					faces.push_back(Face(3, v, NULL, n - 1));
				}
			}
		}
		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		for (Face& face : faces) {
			if (face.normal != -1)
				glNormal3fv(normals[face.normal]);
			else
				glDisable(GL_LIGHTING);
			// set color for the face
			if (face.vertices != NULL) {
				glColor3fv(colors[face.vertices[0]]);
			}
			glBegin(GL_POLYGON);
			for (int i = 0; i < face.edge; i++) {
				glVertex3fv(vertices[face.vertices[i]]);
			}
			glEnd();

			if (face.normal == -1)
				glEnable(GL_LIGHTING);
		}
		glEndList();
		printf("\nModel: %s\n", filename);
		printf("Vertices: %d\n", vertices.size());
		printf("Texcoords: %d\n", texcoords.size());
		printf("Normals: %d\n", normals.size());
		printf("Faces: %d\n", faces.size());
		for (float* f : vertices)
			delete f;
		vertices.clear();
		for (float* f : texcoords)
			delete f;
		texcoords.clear();
		for (float* f : normals)
			delete f;
		normals.clear();
		for (float* f : colors)
			delete f;

		faces.clear();
	}
	void draw() { glCallList(list); }
};

#endif
