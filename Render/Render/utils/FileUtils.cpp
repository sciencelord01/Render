#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Fileutils.h"

#include "../graphics/Mesh.h"
#include "../graphics/shaders/CubeMap.h"

namespace ginkgo {

	std::string FileUtils::read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");	//we read as t -> textfile bc if b -> bytes then it would all be in one line like in bytes
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file); // binary streams -> number of bytes, text streams -> number of characters

		char* data = new char[length + 1]; // + Termination character
		memset(data, 0, length + 1);	//use memset to clear away any binary text
		fseek(file, 0, SEEK_SET);	//Back to beginning
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

	BYTE* FileUtils::loadImage(const char* filename, GLsizei* width, GLsizei* height, double rotationAngleInDegrees)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;

		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;

		if(fmod(rotationAngleInDegrees,360) != 0)
			dib = FreeImage_Rotate(dib, rotationAngleInDegrees);

		if (FreeImage_GetBPP(dib) != 24)
			dib = FreeImage_ConvertTo24Bits(dib);

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		int bits = FreeImage_GetBPP(dib);

		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		return result;
	}

}