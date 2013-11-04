#include "Vector3f.hpp"

#include <iostream>
#include <cmath>

Vector3f::Vector3f(float xi, float yi, float zi){
	x = xi; y = yi; z = zi;
}

Vector3f Vector3f::operator+(const Vector3f& right) const{
	return(Vector3f(x+right.x, y+right.y, z+right.z));
}

Vector3f Vector3f::operator-(const Vector3f& right) const{
	return(Vector3f(x-right.x, y-right.y, z-right.z));
}

float Vector3f::operator*(const Vector3f& right) const{
	return(x*right.x + y*right.y + z*right.z);
}

Vector3f Vector3f::operator*(float right) const{
	return(Vector3f(x*right, y*right, z*right));
}

float Vector3f::Length() const{
	return(sqrt(x*x + y*y + z*z));
}

Vector3f Vector3f::Normalize() const{
	return(Vector3f(*this)*(1.0f/Length()));
}

Vector3f Vector3f::Reflect(const Vector3f& other) const{
	Vector3f norm = Normalize();
	Vector3f otherNorm = other.Normalize();
	return(norm*(otherNorm*norm)*2.0f - otherNorm);
}

Vector3f Vector3f::StealZ(const Vector3f& source) const{
	return(Vector3f(x, y, source.z));
}

Vector3f Vector3f::CrossProduct(const Vector3f& right) const{
	float i = y*right.z - z*right.y;
	float j = - (x*right.z - right.x*z);
	float k = x*right.y - right.x*y;
	return(Vector3f(i,j,k));
}

void Vector3f::Print() const{
	std::cout<<"Vector("<<x<<","<<y<<","<<z<<")";
}
