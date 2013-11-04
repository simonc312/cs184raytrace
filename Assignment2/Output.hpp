#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <FreeImagePlus.h>
#include "Color3f.hpp"

class Output{
public:
	Output(int width, int height);

	void SetPixel(int x, int y, const Color3f& color);

	void Save(const char* name) const;
private:
	fipImage img;
};

#endif//OUTPUT_HPP
