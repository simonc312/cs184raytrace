#include "Attenuation.hpp"

Attenuation::Attenuation(){
	constant = 1.0f;
	linear = 0.0f;
	quadratic = 0.0f;
}

float Attenuation::GetFactor(float distance) const{
	return(1.0f/(constant + (linear + quadratic*distance)*distance));
}
