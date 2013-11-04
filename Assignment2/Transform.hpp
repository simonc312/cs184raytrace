#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Matrix4f.hpp"

class Transform{
public:
	Transform rotate(float x, float y, float z, float angle) const;
	Transform rotateFirst(float x, float y, float z, float angle) const;
	Transform translate(float x, float y, float z) const;
	Transform translateFirst(float x, float y, float z) const;
	Transform scale(float x, float y, float z) const;
	Transform scaleFirst(float x, float y, float z) const;

	Matrix4f Get() const;
	Matrix4f GetInverse() const;
private:
	Matrix4f foreward, backward;
};

#endif//TRANSFORM_HPP
