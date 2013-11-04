#include "Matrix3f.hpp"

#include <iostream>
#include <math.h>
#define PI 3.14159265f

Matrix3f::Matrix3f(){
	//Automatically set as Identity Matrix
	for(int row=0;row < 3;row++){
		for(int col=0;col < 3;col++){
			data[row][col] = (row==col)?(1):(0);
		}
	}
}

Matrix3f::Matrix3f(const Vector3f& col1, const Vector3f& col2, const Vector3f& col3){
	data[0][0] = col1.x; data[1][0] = col1.y; data[2][0] = col1.z;
	data[0][1] = col2.x; data[1][1] = col2.y; data[2][1] = col2.z;
	data[0][2] = col3.x; data[1][2] = col3.y; data[2][2] = col3.z;
}

float Matrix3f::Determinate() const{
	float ret;
	ret  = data[0][0]*(data[1][1]*data[2][2]-data[1][2]*data[2][1]);
	ret -= data[0][1]*(data[1][0]*data[2][2]-data[1][2]*data[2][0]);
	ret += data[0][2]*(data[1][0]*data[2][1]-data[1][1]*data[2][0]);
	return(ret);
}

Matrix3f Matrix3f::SetColumn(int column, const Vector3f& vector) const{
	Matrix3f ret(*this);
	if(column < 3){
		ret.data[0][column] = vector.x;
		ret.data[1][column] = vector.y;
		ret.data[2][column] = vector.z;
	}
	return(ret);
}

Vector3f Matrix3f::Solve(const Vector3f& constants) const{
	float det = Determinate();
	float x = SetColumn(0, constants).Determinate() / det;
	float y = SetColumn(1, constants).Determinate() / det;
	float z = SetColumn(2, constants).Determinate() / det;
	return(Vector3f(x, y, z));
}

Matrix3f Matrix3f::operator * (const Matrix3f& right) const{
	Matrix3f new_matrix;
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

Vector3f Matrix3f::operator * (const Vector3f& right) const{
	Vector3f new_vector;
	new_vector.x = data[0][0]*right.x + data[0][1]*right.y + data[0][2]*right.z;
	new_vector.y = data[1][0]*right.x + data[1][1]*right.y + data[1][2]*right.z;
	new_vector.z = data[2][0]*right.x + data[2][1]*right.y + data[2][2]*right.z;
	return(new_vector);
}

Vertex3f Matrix3f::operator * (const Vertex3f& right) const{
	Vertex3f new_vertex;
	new_vertex.x = data[0][0]*right.x + data[0][1]*right.y + data[0][2]*right.z;
	new_vertex.y = data[1][0]*right.x + data[1][1]*right.y + data[1][2]*right.z;
	new_vertex.z = data[2][0]*right.x + data[2][1]*right.y + data[2][2]*right.z;
	return(new_vertex);
}

void Matrix3f::Print() const{
	std::cout<<"Matrix3f(";
	for(int row=0; row<3;row++){
		std::cout<<"["<<data[row][0]<<","<<data[row][1]<<","<<data[row][2]<<"] ";
	}
	std::cout<<")";
}


