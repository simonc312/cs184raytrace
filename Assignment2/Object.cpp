#include "Object.hpp"

#include <iostream>

bool Object::IsTriangle() const{ return(false); }

bool Object::GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const{
	return(false);
}

void Object::Debug() const{ }
