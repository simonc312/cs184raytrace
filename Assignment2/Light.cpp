#include "Light.hpp"

Light::Light(const Color3f& icolor, LightType itype, const Attenuation& iattenuation){
	color = icolor;
	type = itype;
	attenuation = iattenuation;
}
