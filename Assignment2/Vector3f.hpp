#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

class Vector3f;

#include "Vertex3f.hpp"

class Vector3f{
public:
	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Vector3f operator+(const Vector3f& right) const;
	Vector3f operator-(const Vector3f& right) const;
	float operator*(const Vector3f& right) const;
	Vector3f operator*(float right) const;
	float Length() const;
	Vector3f Normalize() const;
	Vector3f Reflect(const Vector3f& other) const;//Reflect another vector about self (self=normal). Normalizes result.
	Vector3f CrossProduct(const Vector3f& right) const;
	Vector3f StealZ(const Vector3f& source) const;
	
	void Print() const;

	friend class Matrix4f;
	friend class Matrix3f;
	friend class Vertex3f;
private:
	float x, y, z;
};

#endif//VECTOR3F_HPP
