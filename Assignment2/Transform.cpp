#include "Transform.hpp"

Transform Transform::rotate(float x, float y, float z, float angle) const{
	Transform ret;

	ret.foreward = foreward.rotate(x, y, z, angle);
	ret.backward = backward.rotateFirst(x, y, z, -angle);

	return(ret);
}

Transform Transform::rotateFirst(float x, float y, float z, float angle) const{
	Transform ret;

	ret.foreward = foreward.rotateFirst(x, y, z, angle);
	ret.backward = backward.rotate(x, y, z, -angle);

	return(ret);
}

Transform Transform::translate(float x, float y, float z) const{
	Transform ret;

	ret.foreward = foreward.translate(x, y, z);
	ret.backward = backward.translateFirst(-x, -y, -z);

	return(ret);
}

Transform Transform::translateFirst(float x, float y, float z) const{
	Transform ret;

	ret.foreward = foreward.translateFirst(x, y, z);
	ret.backward = backward.translate(-x, -y, -z);

	return(ret);
}

Transform Transform::scale(float x, float y, float z) const{
	Transform ret;

	ret.foreward = foreward.scale(x, y, z);
	ret.backward = backward.scaleFirst(1.0f/x, 1.0f/y, 1.0f/z);//TODO: Make safe someday...

	return(ret);
}

Transform Transform::scaleFirst(float x, float y, float z) const{
	Transform ret;

	ret.foreward = foreward.scaleFirst(x, y, z);
	ret.backward = backward.scale(1.0f/x, 1.0f/y, 1.0f/z);//TODO: Make safe someday...

	return(ret);
}

Matrix4f Transform::Get() const{ return(foreward); }

Matrix4f Transform::GetInverse() const{ return(backward); }

