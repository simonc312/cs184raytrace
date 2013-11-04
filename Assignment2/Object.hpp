#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Ray.hpp"
#include "Transform.hpp"
#include "Quality.hpp"

class Object{
public:
	virtual bool GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const;

	virtual bool IsTriangle() const;

	virtual void Debug() const;

	Quality qualities;
protected:
	Transform transform;//From local to global.
};

#endif//OBJECT_HPP
