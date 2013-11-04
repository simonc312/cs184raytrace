#include <iostream>

using namespace std;

#include "Scene.hpp"
#include "Output.hpp"

#include <cstdlib>
#include <time.h>
#include <math.h>
#define PI 3.14159265f

bool dbg;

#define EPSILON 0.0001

bool GetClosestIntersection(Scene& scene, const Ray& ray, Vertex3f& intersection, Vector3f& normal,
                            float& distance, Object* & object, float minDistance = EPSILON){
	Vertex3f inter;
	Vector3f norm;
	float dist;
	bool found = false;
	std::list<Object*>::iterator obj = scene.objects.begin();
	while(obj != scene.objects.end()){
		if((*obj)->GetIntersection(ray, inter, norm)){
			dist = (inter - ray.origin).Length();
			if(dist > minDistance){//Prevent origin of ray from being intersection...
				if(!found || dist < distance){
					distance = dist;
					intersection = inter;
					normal = norm;
					object = *obj;
					found = true;
				}
			}
		}
		obj++;
	}
	cout.flush();
	return(found);
}

#undef EPSILON

int main(int argc, char *argv[]){
	time_t startTime = time(NULL);	

	if(argc < 2){ cerr<<"No file specified.\n"; return(0); }
	int progressWait = 2;
	bool showProgress = (progressWait > 0);
	Scene scene(argv[1], progressWait);
	Output out(scene.imgWidth, scene.imgHeight);

	int size = (scene.imgWidth)*(scene.imgHeight);
	int curDone = 0;

	cout<<"Preliminary check: objects: "<<scene.objects.size()<<";";
	cout<<" lights: "<<scene.lights.size()<<"; reflection depth: "<<scene.maxDepth<<"; pixels: "<<size<<";\n";

	cout<<"Starting Ray-Tracing.\n";

	time_t lastUpdate, curTime;
	if(showProgress){
		cout<<"Ray-Tracing completed: 0%";
		lastUpdate = time(NULL);
	}
	cout.flush(); 

	Vector3f foreward = (scene.lookToward - scene.lookFrom).Normalize();
	Vector3f right = foreward.CrossProduct(scene.up).Normalize();
	Vector3f up = foreward.CrossProduct(right).Normalize();
	/*float radPerPixel = (PI*scene.fov/180.0f)/((float)scene.imgHeight);*/
	float pixelSize = 2.0f*(tan(PI*scene.fov/360.0f))/((float)scene.imgHeight);
	up = up * pixelSize; right = right * pixelSize;
	float leftOffset = ( ((float)scene.imgWidth) - 1.0f )/2.0f;
	float upOffset = ( ((float)scene.imgHeight) - 1.0f )/2.0f;
	Vertex3f topLeft = scene.lookFrom + foreward - right*leftOffset + up*upOffset;
	Vertex3f origin;
	Ray ray(origin, up), lRay(origin, up);//Use random values.
	Color3f black(0.0f, 0.0f, 0.0f);
	for(int x = 0;x < scene.imgWidth;x++){
		for(int y = 0;y < scene.imgHeight;y++){
			dbg = (300 == x && (214 == y || 215 == y));
			//Get the ray to cast.
			/*float xDeg = (((float)x) - ((float)scene.imgWidth)/2.0f - 0.5f)*radPerPixel;
			float yDeg = (((float)y) - ((float)scene.imgHeight)/2.0f - 0.5f)*radPerPixel;
			ray.direction = (foreward + up*tan(-yDeg) + right*tan(-xDeg)).Normalize();*/
			ray.origin = scene.lookFrom;
			Vertex3f screenPos = topLeft + right*((float)x) - up*((float)y);
			ray.direction = (screenPos - ray.origin).Normalize();
			Color3f sum;
			Color3f depthAttenuation(1.0f, 1.0f, 1.0f);
			for(int depth = 0;depth < scene.maxDepth;depth++){
				//Find the closest intersection.
				Vertex3f intersection;
				Vector3f normal;
				float distance;
				Object* object;
				if(GetClosestIntersection(scene, ray, intersection, normal, distance, object)){
					normal = normal.Normalize();
					Quality quality = object->qualities;
					//Do shading.
					Color3f localColor;
					std::list<Light*>::iterator light = scene.lights.begin();
					while(light != scene.lights.end()){
						//Get the required ray.
						switch((*light)->type){
						case Light::Point:
							{
								PointLight* ptLight = (PointLight*)(*light);
								lRay.origin = intersection;
								lRay.direction = (ptLight->position - intersection).Normalize();
								Vertex3f inter; Vector3f norm; float dist; Object* obj;
								bool exists = GetClosestIntersection(scene, lRay, inter, norm, dist, obj);
								float lightDistance = (intersection - ptLight->position).Length();
								//Orient its normal to be on same side as outgoing lRay.
								if(object->IsTriangle() && 0.0f > lRay.direction*normal){
									normal = normal * -1.0f;
								}
								bool onRightSide = (0.0f > normal*ray.direction);
								if(onRightSide && (dist > lightDistance || !exists)){//Its not shadowed.
									//Calculate the diffuse color.
									float attFactor = ptLight->attenuation.GetFactor(lightDistance);
									float factor = lRay.direction*normal;
									if(factor < 0.0f){ factor = 0.0f; }
									localColor = localColor + (quality.diffuse)*(ptLight->color)*factor*attFactor;
									//Calculate the specular color.
									factor = (ray.direction * -1.0f) * normal.Reflect(lRay.direction);
									if(factor < 0.0f){ factor = 0.0f; }
									factor = pow(factor, quality.shininess);
									localColor = localColor + (quality.specular)*(ptLight->color)*factor*attFactor;
								}
							}
							break;
						case Light::Directional:
							{
								DirectionalLight* dirLight = (DirectionalLight*)(*light);
								lRay.origin = intersection;
								lRay.direction = (dirLight->direction)*-1.0f;
								Vertex3f inter; Vector3f norm; float dist; Object* obj;
								bool exists = GetClosestIntersection(scene, lRay, inter, norm, dist, obj);
								//Orient its normal to be on same side as outgoing lRay.
								if(object->IsTriangle() && 0.0f > lRay.direction*normal){
									normal = normal * -1.0f;
								}
								bool onRightSide = (0.0f > normal*ray.direction);
								if(onRightSide && !exists){//Its not shadowed!!!!!!
									//Calculate the diffuse color.
									float factor = (lRay.direction*normal);
									if(factor < 0.0f){ factor = 0.0f; }
									localColor = localColor + (quality.diffuse)*(dirLight->color)*factor;
									//Calculate the specular color.
									factor = (ray.direction * -1.0f) * normal.Reflect(lRay.direction);
									if(factor < 0.0f){ factor = 0.0f; }
									factor = pow(factor, quality.shininess);
									localColor = localColor + (quality.specular)*(dirLight->color)*factor;
								}
							}
							break;
						}
						//Next!
						light++;
					}
					localColor = localColor + quality.emission;
					if(!scene.lights.empty()){ localColor = localColor + quality.ambient; }
					sum = sum + localColor * depthAttenuation;
					depthAttenuation = depthAttenuation * quality.specular;
					//Calculate the reflected ray.
					ray.origin = intersection;
					if(0.0f > normal * ray.direction && object->IsTriangle()){ normal = normal * -1.0f; }
					ray.direction = normal.Reflect(ray.direction) * -1.0f;
				}else{
					break;					
				}
			}
			out.SetPixel(x, y, sum);
			//Update progress if necessary.
			curDone++;
			curTime = time(NULL);
			if(showProgress && difftime(curTime, lastUpdate) > progressWait){
				double whole;
				modf(10000.0f*((float)curDone)/((float)size), &whole);
				cout<<" ... "<<(whole/100.0f)<<"%";
				cout.flush();
				lastUpdate = curTime;
			}
		}
	}
	const char* fileName = scene.outputName.c_str();
	cout<<" Done!\nWriting to file \""<<fileName<<"\" ...";
	out.Save(fileName);
	time_t endTime = time(NULL);
	int elapsed = difftime(endTime, startTime);
	cout<<" Done!\nElapsed time: ";
	cout<<(elapsed % 60)<<" seconds ";
	if(elapsed > 60){
		elapsed /= 60; cout<<(elapsed % 60)<<" minutes ";
		if(elapsed > 60){
			elapsed /= 60; cout<<(elapsed % 60)<<" hours ";
			if(elapsed > 24){
				elapsed /= 24; cout<<(elapsed % 24)<<" days ";
				if(elapsed >  7){
					elapsed /= 7; cout<<(elapsed % 7)<<" weeks ";
					if(elapsed > 52){
						elapsed /= 52; cout<<elapsed<<" years!?!";
					}
				}
			}
		}
	}
	cout<<"\n";
	return(0);
}
