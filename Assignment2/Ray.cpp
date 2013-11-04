#include "Ray.hpp"

Ray::Ray(const Vertex3f& origin1, const Vector3f& direction1){
	origin = origin1;
	direction = direction1.Normalize();
}

Ray Ray::operator*(const Matrix4f& matrix) const{
       return(Ray(matrix*origin, matrix*direction)); 
}

#include <iostream>

void Ray::Print() const{
	std::cout<<"Ray(";
	origin.Print();
	std::cout<<",";
	direction.Print();
	std::cout<<")";
}
