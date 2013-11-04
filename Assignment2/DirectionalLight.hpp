#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"
#include "Vector3f.hpp"

class DirectionalLight : public Light{
public:
	DirectionalLight(const Vector3f& idirection, const Color3f& icolor, const Attenuation& iattenuation);
	Vector3f direction; //Stored in global coordinates. From the light!
};

#endif//DIRECTIONALLIGHT_HPP
