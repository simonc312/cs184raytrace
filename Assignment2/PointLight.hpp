#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"
#include "Vertex3f.hpp"

class PointLight : public Light{
public:
	PointLight(const Vertex3f& iposition, const Color3f& icolor, const Attenuation& iattenuation);
	Vertex3f position; //Stores in global coordinates.
};

#endif//POINTLIGHT_HPP
