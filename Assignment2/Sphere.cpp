#include "Sphere.hpp"

#include <math.h>

Sphere::Sphere(float x, float y, float z, float radius, const Transform& toGlobal, const Quality& iquality){
	//Make it a unit-sphere scaled then translated to create the wanted sphere.
	transform = toGlobal.translateFirst(x, y, z).scaleFirst(radius, radius, radius);
	qualities = iquality;
}

#include <iostream>

using namespace std;
extern bool dbg;

#define EPSILON 0.00001

bool Sphere::GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const{
	Ray rayLocal = ray*transform.GetInverse();

	Vector3f pmc = rayLocal.origin - Vertex3f(0.0f, 0.0f, 0.0f);
	float b = rayLocal.direction*pmc;
	float det = b*b - pmc*pmc + 1; //1 represents radius*radius = 1
	if(det < EPSILON){ return(false); }
	float d1 = -b + sqrt(det), d2 = -b - sqrt(det);
	//Get the points.
	Vertex3f intersect1 = rayLocal.origin + rayLocal.direction*d1;
	Vertex3f intersect2 = rayLocal.origin + rayLocal.direction*d2;
	//IGNORE values behind the starting point!
	bool ign1 = (d1 < EPSILON), ign2 = (d2 < EPSILON);
	if(ign1 && ign2){ return(false); }
	if(ign1 && (!ign2)){
		intersection = intersect2;
		normal = intersection - Vertex3f(0.0,0.0,0.0);
		intersection = transform.Get()*intersection;
		normal = transform.GetInverse().transpose()*normal;
		return(true);
	}
	if((!ign1) && ign2){
		intersection = intersect1;
		normal = intersection - Vertex3f(0.0,0.0,0.0);
		intersection = transform.Get()*intersection;
		normal = transform.GetInverse().transpose()*normal;
		return(true);
	}
	//Return the closest.
	float length1 = (rayLocal.origin - intersect1).Length();
	float length2 = (rayLocal.origin - intersect2).Length();
	if(length1 < length2){
		intersection = intersect1;
	}else{
		intersection = intersect2;
	}
	normal = intersection - Vertex3f(0.0,0.0,0.0);
	intersection = transform.Get()*intersection;
	normal = transform.GetInverse().transpose()*normal;
	return(true);
}

#undef EPSILON

bool Sphere::IsTriangle() const{ return(false); }

void Sphere::Debug() const{
	std::cout<<"Transform: ";
}
