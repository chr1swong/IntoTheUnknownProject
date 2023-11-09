#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	unsigned int ID;
	int width;
	int height;
	unsigned char* pixels;

	~Texture();

	int Initialise(char* file_name);
	int Create_BITMAP_RGB(char* file_name);

};

void Textures_Initialise();

#endif