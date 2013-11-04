#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(const Vector3f& idirection, const Color3f& icolor,
                                   const Attenuation& iattenuation)
                 :Light(icolor, Directional, iattenuation){
	direction = idirection.Normalize();
}

