#ifndef MATRIX4F_HPP
#define MATRIX4F_HPP

#include "Vector3f.hpp"
#include "Vertex3f.hpp"

class Matrix4f {
public: 
	Matrix4f();
	Matrix4f rotate(const Vector3f& axis, float angle) const;
	Matrix4f rotate(float x, float y, float z, float angle) const;
	Matrix4f rotateFirst(float x, float y, float z, float angle) const;
	Matrix4f translate(const Vector3f& movement) const;
	Matrix4f translate(float x, float y, float z) const;
	Matrix4f translateFirst(float x, float y, float z) const;
	Matrix4f scale(float x, float y, float z) const;
	Matrix4f scaleFirst(float x, float y, float z) const;
	Matrix4f transpose() const;
	Matrix4f operator * (const Matrix4f& right) const;
	Vector3f operator * (const Vector3f& right) const;
	Vertex3f operator * (const Vertex3f& right) const;

	void Print() const;
protected:
	static Matrix4f makeRotation(float x, float y, float z, float angle);
	static Matrix4f makeTranslation(float x, float y, float z);
	static Matrix4f makeScaling(float x, float y, float z);
private:
	float data[4][4];
};

#endif//MATRIX4F_HPP
