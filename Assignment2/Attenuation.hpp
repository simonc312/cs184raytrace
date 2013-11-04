#ifndef ATTENUATION_HPP
#define ATTENUATION_HPP

class Attenuation{
public:
	Attenuation();

	float GetFactor(float distance) const;

	float constant;
	float linear;
	float quadratic;
};

#endif//ATTENUATION_HPP
