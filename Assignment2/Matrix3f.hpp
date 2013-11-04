#ifndef MATRIX3F_HPP
#define MATRIX3F_HPP

#include "Vector3f.hpp"
#include "Vertex3f.hpp"

class Matrix3f {
public:
	Matrix3f();
	Matrix3f(const Vector3f& col1, const Vector3f& col2, const Vector3f& col3);
	float Determinate() const;
	Matrix3f SetColumn(int column, const Vector3f& vector) const;
	Vector3f Solve(const Vector3f& constants) const;//Returns x that solves equation constants = this*x
	Matrix3f operator * (const Matrix3f& right) const;
	Vector3f operator * (const Vector3f& right) const;
	Vertex3f operator * (const Vertex3f& right) const;

	void Print() const;
protected:
	//
private:
	float data[3][3];
};

#endif//MATRIX3F_HPP
