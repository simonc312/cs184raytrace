#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3f.hpp"
#include "Vertex3f.hpp"
#include "Matrix4f.hpp"

class Ray{
public:
	Ray(const Vertex3f& origin1, const Vector3f& direction1);
	Ray operator*(const Matrix4f& matrix) const;

	void Print() const;

	Vertex3f origin;
	Vector3f direction;
};

#endif//RAY_HPP
