#include "PointLight.hpp"

PointLight::PointLight(const Vertex3f& iposition, const Color3f& icolor,
                       const Attenuation& iattenuation)
           :Light(icolor, Point, iattenuation){
	position = iposition;
}

