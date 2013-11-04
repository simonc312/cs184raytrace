#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

class Sphere : public Object{
public:
	Sphere(float x, float y, float z, float radius, const Transform& toGlobal, const Quality& iquality);

	bool GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const;

	bool IsTriangle() const;

	void Debug() const;
};

#endif//SPHERE_HPP
