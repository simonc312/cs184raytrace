#ifndef VERTEX3F_HPP
#define VERTEX3F_HPP

class Vertex3f;

#include "Vector3f.hpp"

class Vertex3f {
public:
	Vertex3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Vertex3f operator+(const Vector3f& right) const;
	Vertex3f operator-(const Vector3f& right) const;
	Vector3f operator-(const Vertex3f& right) const;
	Vertex3f operator*(const float right) const;

	void Print() const;

	friend class Matrix4f;
	friend class Matrix3f;
	friend class Vector3f;
private: 
	float x, y, z;
};

#endif//VERTEX3F_HPP
