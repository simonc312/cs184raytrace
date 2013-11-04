#include "Triangle.hpp"
#include "Matrix3f.hpp"

Triangle::Triangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3,
                   const Transform& toGlobal, const Quality& quality){
	vertex1 = v1; vertex2 = v2; vertex3 = v3;
	surfaceNormal = normal3 = normal2 = normal1 = (v2-v1).CrossProduct(v3-v1).Normalize();
	transform = toGlobal;
	qualities = quality;
}

Triangle::Triangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3,
	         const Vector3f& n1, const Vector3f& n2, const Vector3f& n3,
	         const Transform& toGlobal, const Quality& quality){
	vertex1 = v1; vertex2 = v2; vertex3 = v3;
	normal1 = n1.Normalize(); normal2 = n2.Normalize(); normal3 = n3.Normalize();
	surfaceNormal = (v2-v1).CrossProduct(v3-v1).Normalize();
	transform = toGlobal;
	qualities = quality;
}

#define EPSILON 0.0000001

bool Triangle::GetIntersection(const Ray& ray, Vertex3f& intersection, Vector3f& normal) const{
	Ray rayLocal = ray*transform.GetInverse();
	//First find intersection of ray and plane.
	if(rayLocal.direction * surfaceNormal < EPSILON && rayLocal.direction * surfaceNormal > -EPSILON){
		return(false);//Ray is parallel to surface.
	}
	//Parameterize in terms of vectors from v1 to v2 and v3.
	Vector3f i = vertex2 - vertex1;
	Vector3f j = vertex3 - vertex1;
	//Create and solve the resulting linear system.
	Matrix3f intersect(i, j, rayLocal.direction*-1.0f);
	Vector3f param = intersect.Solve(rayLocal.origin - vertex1);
	float x = param*Vector3f(1.0f, 0.0f, 0.0f);
	float y = param*Vector3f(0.0f, 1.0f, 0.0f);
	float t = param*Vector3f(0.0f, 0.0f, 1.0f);
	//Then the intersection is at.
	intersection = rayLocal.origin+rayLocal.direction*t;//Equivalently (vertex1+i*x+j*y)...
	//Check that the intersection is within the triangle.
	if(-EPSILON > x || -EPSILON > y || -EPSILON < x + y - 1.0f){ return(false); }
	//Check if the intersection is on the ray (not behind).
	if(-EPSILON > t){ return(false); }
	//Must be in triangle now! Do linear interpolation to find normal.
	float z = 1 - x - y;//This makes intersection = vertex1*x + vertex2*y + vertex3*z
	normal = normal1*z + normal2*x + normal3*y;
	//Transform back to global coordinates.
	intersection = transform.Get()*intersection;
	normal = transform.GetInverse().transpose()*normal;
	return(true);
}

#undef EPSILON

bool Triangle::IsTriangle() const{ return(true); }

void Triangle::Debug() const{
	//
}
