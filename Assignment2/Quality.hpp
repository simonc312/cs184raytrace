#ifndef QUALITIES_HPP
#define QUALITIES_HPP

#include "Color3f.hpp"

class Quality{
public:
	Quality();

	Color3f ambient;
	Color3f diffuse;
	Color3f specular;
	float shininess;//Specular power.
	Color3f emission;
};

#endif//QUALITIES_HPP
