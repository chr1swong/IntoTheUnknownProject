#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Texture.h"

Texture::~Texture() {
	if (pixels) delete pixels;
	pixels = NULL;
}

void Textures_Initialise()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

int Texture::Initialise(char* file_name)
{
	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);

	if (!Create_BITMAP_RGB(file_name)) return 0;

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height,
		GL_RGB, GL_UNSIGNED_BYTE, pixels);
	return 1;
}

int Texture::Create_BITMAP_RGB(char* file_name)
{
	BITMAPINFOHEADER info_header;
	BITMAPFILEHEADER file_header;
	FILE* file;

	fopen_s(&file, file_name, "r");
	//if(file == NULL) return NULL;

	fread(&file_header, sizeof(BITMAPFILEHEADER), 1, file);

	if (file_header.bfType != 0x4D42)
	{
		fclose(file);
		return NULL;
	}

	fread(&info_header, sizeof(BITMAPINFOHEADER), 1, file);

	fseek(file, file_header.bfOffBits, SEEK_SET);

	height = info_header.biHeight;
	width = info_header.biWidth;

	pixels = new unsigned char[info_header.biSizeImage];

	if (!pixels)
	{
		delete pixels;
		fclose(file);
		return NULL;
	}

	fread(pixels, info_header.biSizeImage, 1, file);

	if (pixels == NULL)
	{
		delete pixels;
		fclose(file);
		return NULL;
	}

	unsigned char Temp;
	for (int a = 0; a < info_header.biSizeImage; a += 3)
	{
		Temp = pixels[a];
		pixels[a] = pixels[a + 2];
		pixels[a + 2] = Temp;
	}

	// flip the bitmap
	unsigned char* temp = new unsigned char[info_header.biSizeImage];

	memcpy(temp, pixels, info_header.biSizeImage);

	for (int a = 0; a < height; a++)
	{
		memcpy(&pixels[((height - 1) - a) * width * 3], &temp[a * width * 3], width * 3);
	}

	if (temp) delete temp;

	fclose(file);

	return 1;
}