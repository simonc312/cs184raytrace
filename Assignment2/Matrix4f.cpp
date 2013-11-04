#include "Matrix4f.hpp"

#include <math.h>
#define PI 3.14159265f

Matrix4f::Matrix4f(){
	//Automatically set as Identity Matrix
	for(int row=0; row<4;row++){
		for(int column=0; column<4;column++){
			data[row][column] = (row==column)?(1):(0);
		}
	}
}

Matrix4f Matrix4f::rotate(const Vector3f& axis, float angle) const{
	Vector3f normalized = axis.Normalize();
	return(rotate(normalized.x, normalized.y, normalized.z, angle));
}

Matrix4f Matrix4f::rotate(float x, float y, float z, float angle) const{
	return(makeRotation(x, y, z, angle) * Matrix4f(*this));
}

Matrix4f Matrix4f::rotateFirst(float x, float y, float z, float angle) const{
	return(Matrix4f(*this) * makeRotation(x, y, z, angle));
}

Matrix4f Matrix4f::translate(const Vector3f& movement) const{
	return(translate(movement.x, movement.y, movement.z));
}

Matrix4f Matrix4f::translate(float x, float y, float z) const{
	return(makeTranslation(x, y, z) * Matrix4f(*this));
}

Matrix4f Matrix4f::translateFirst(float x, float y, float z) const{
	return(Matrix4f(*this) * makeTranslation(x, y, z));
}

Matrix4f Matrix4f::scale(float x, float y, float z) const{
	return(makeScaling(x, y, z) * Matrix4f(*this));
}

Matrix4f Matrix4f::scaleFirst(float x, float y, float z) const{
	return(Matrix4f(*this) * makeScaling(x, y, z));
}

Matrix4f Matrix4f::transpose() const{
	Matrix4f ret;
	for(int row=0;row<4;row++){
		for(int column=0;column<4;column++){
			ret.data[row][column] = data[column][row];
		}
	}
	return(ret);
}

Matrix4f Matrix4f::operator * (const Matrix4f& right) const{
	Matrix4f new_matrix;
	for(int row=0;row<4;row++){
		for(int column=0;column<4;column++){
			float sum=0;
			for(int element=0;element<4;element++){
			sum += data[row][element]*right.data[element][column];
			}
			new_matrix.data[row][column] = sum;
		}
	}
	return new_matrix;
}

Vector3f Matrix4f::operator * (const Vector3f& right) const{
	Vector3f new_vector;
		new_vector.x = data[0][0]*right.x + data[0][1]*right.y + data[0][2]*right.z;
		new_vector.y = data[1][0]*right.x + data[1][1]*right.y + data[1][2]*right.z;
		new_vector.z = data[2][0]*right.x + data[2][1]*right.y + data[2][2]*right.z;
	return new_vector;
}

Vertex3f Matrix4f::operator * (const Vertex3f& right) const{
	Vertex3f new_vertex;
		new_vertex.x = data[0][0]*right.x + data[0][1]*right.y + data[0][2]*right.z + data[0][3];
		new_vertex.y = data[1][0]*right.x + data[1][1]*right.y + data[1][2]*right.z + data[1][3];
		new_vertex.z = data[2][0]*right.x + data[2][1]*right.y + data[2][2]*right.z + data[2][3];
		float w = data[3][0]*right.x + data[3][1]*right.y + data[3][2]*right.z + data[3][3];
		new_vertex = new_vertex*(1.0f/w);
	return new_vertex;
}

#include <iostream>

void Matrix4f::Print() const{
	std::cout<<"Matrix4f(";
	for(int row=0; row<4;row++){
		std::cout<<"["<<data[row][0]<<","<<data[row][1]<<","<<data[row][2]<<","<<data[row][3]<<"] ";
	}
	std::cout<<")";
}

Matrix4f Matrix4f::makeRotation(float x, float y, float z, float angle){
	float len = sqrt(x*x + y*y + z*z);
	x /= len; y /= len; z /= len;

	Matrix4f rotation;
	float c = cos(angle*PI/180.0f), s = sin(angle*PI/180.0f);
	float ic = 1.0f - c;
	rotation.data[0][0] = c+x*x*ic;
	rotation.data[0][1] = x*y*ic - z*s;
	rotation.data[0][2] = x*z*ic + y*s;

	rotation.data[1][0] = y*x*ic + z*s;
	rotation.data[1][1] = c + y*y*ic;
	rotation.data[1][2] = y*z*ic - x*s;

	rotation.data[2][0] = z*x*ic - y*s;
	rotation.data[2][1] = z*y*ic + x*s;
	rotation.data[2][2] = c + z*z*ic;
	return(rotation);
}

Matrix4f Matrix4f::makeTranslation(float x, float y, float z){
	Matrix4f translation;
	translation.data[0][3] = x;
	translation.data[1][3] = y;
	translation.data[2][3] = z;
	return(translation);
}

Matrix4f Matrix4f::makeScaling(float x, float y, float z){
	Matrix4f scaling;
	scaling.data[0][0] = x;
	scaling.data[1][1] = y;
	scaling.data[2][2] = z;
	return(scaling);
}

