#include "Vertex3f.hpp"

#include <iostream>

Vertex3f::Vertex3f(float xi, float yi, float zi){
	x = xi; y= yi; z=zi;
}

Vertex3f Vertex3f::operator+(const Vector3f& right) const{
	return(Vertex3f(x+right.x, y+right.y, z+right.z));
}

Vertex3f Vertex3f::operator-(const Vector3f& right) const{
	return(Vertex3f(x-right.x, y-right.y, z-right.z));
}


Vector3f Vertex3f::operator-(const Vertex3f& right) const{
	return(Vector3f(x-right.x, y-right.y, z-right.z));
}

Vertex3f Vertex3f::operator*(float right) const{
	return(Vertex3f(x*right, y*right, z*right));
}

void Vertex3f::Print() const{
	std::cout<<"Vertex("<<x<<","<<y<<","<<z<<")";
}


