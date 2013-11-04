#include "Color3f.hpp"

Color3f::Color3f(float r, float g, float b){
	red = r; green = g; blue = b;
}

Color3f Color3f::operator+(const Color3f& right) const{
	return(Color3f(red+right.red, green+right.green, blue+right.blue));
}

Color3f Color3f::operator*(const Color3f& right) const{
	return(Color3f(red*right.red, green*right.green, blue*right.blue));
}

Color3f Color3f::operator*(float right) const{
	return(Color3f(red*right, green*right, blue*right));
}

float Color3f::Red() const{ return(red); }

float Color3f::Green() const{ return(green); }

float Color3f::Blue() const{ return(blue); }

#include <iostream>

void Color3f::Print() const{ std::cout<<"Color3f("<<red<<","<<green<<","<<blue<<")"; }
