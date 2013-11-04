#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"

class Triangle :public Object {
public:
	Triangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3,
	         const Transform& toGlobal, const Quality& quality);
	Triangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3,
	         const Vector3f& n1, const Vector3f& n2, const Vector3f& n3,
	         const Transform& toGlobal, const Quality& quality);

	bool GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const;

	bool IsTriangle() const;

	void Debug() const;
private:
	Vertex3f vertex1, vertex2, vertex3;
	Vector3f normal1, normal2, normal3;
	Vector3f surfaceNormal;
};

#endif//TRIANGLE_HPP
