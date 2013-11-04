#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Color3f.hpp"
#include "Ray.hpp"
#include "Attenuation.hpp"

class Light{
public:
	enum LightType{ Point, Directional };

	Light(const Color3f& icolor, LightType itype, const Attenuation& attenuation);

	LightType type;
	Color3f color;
	Attenuation attenuation;
};

#endif//LIGHT_HPP
