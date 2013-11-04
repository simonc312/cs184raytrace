#include "Output.hpp"

#include <math.h>

Output::Output(int width, int height)
       :img(FIT_BITMAP, width, height, 24){ }

void Output::SetPixel(int x, int y, const Color3f& color){
	RGBQUAD px;
	px.rgbRed = 255.0f*fmin(color.Red(), 1.0f);
	px.rgbGreen = 255.0f*fmin(color.Green(), 1.0f);
	px.rgbBlue = 255.0f*fmin(color.Blue(), 1.0f);
	img.setPixelColor(x, y, &px);
}

void Output::Save(const char* name) const{
	img.save(name, PNG_Z_NO_COMPRESSION);
}
