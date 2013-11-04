#include "Scene.hpp"

#include <iostream>

using namespace std;

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <math.h>
#include <time.h>

Scene::Scene(std::string file, int progressWait){
	bool showProgress = (progressWait > 0);
	//store variables and set stuff at the end
	outputName = "output.png";

	ifstream in(file.c_str());
	if(!in.is_open()){
		cout << "Unable to open file" << std::endl;
	}else{
		cout<<"Attempting read of file \""<<file.c_str()<<"\".\n";

		//Default values.
		maxDepth = 5;

		in.seekg(0, std::ios_base::end); 
		int fileSize = in.tellg(), fileDone;
		in.seekg(0, std::ios_base::beg);

		cout<<"Preliminary check: Size: ";
		float displaySize = fileSize;
		if(displaySize > 1024.0f){
			double whole;
			displaySize /= 1024.0f;
			modf(displaySize*100.0f, &whole);
			if(displaySize > 1024.0f){
				displaySize /= 1024.0f;
				modf(displaySize*100.0f, &whole);
				if(displaySize > 1024.0f){
					displaySize /= 1024.0f;
					modf(displaySize*100.0f, &whole);
					if(displaySize > 1024.0f){
						displaySize /= 1024.0f;
						modf(displaySize*100.0f, &whole);
						cout<<(whole/100.0f)<<"GiB.\n";
					}else{ cout<<(whole/100.0f)<<"MiB.\n"; }
				}else{ cout<<(whole/100.0f)<<"KiB.\n"; }
			}else{ cout<<(whole/100.0f)<<"B.\n"; }
		}else{ cout<<displaySize<<"b.\n"; }

		string line;
		
		stack<Transform> transformStack;
		Transform curTransform;
		Quality curQuality;
		Attenuation curAttenuation;

		time_t lastUpdate, curTime;
		if(showProgress){
			cout<<"Reading completed: 0%";
		}
		lastUpdate = time(NULL);

		while(in.good()){
			vector<std::string> splitline;
			string buf;

			getline(in,line);
			stringstream ss(line);

			while(ss >> buf){
				splitline.push_back(buf);
			}
			//Ignore blank lines
			if(splitline.size() == 0){
				continue;
			}

			//Ignore comments
			if(splitline[0][0] == '#'){
				continue;
			}

			//Valid commands:
			//size width height
			//	must be first command of file, controls image size
			else if(!splitline[0].compare("size")){
				imgWidth = atoi(splitline[1].c_str());
				imgHeight = atoi(splitline[2].c_str());
			}
			//maxdepth depth
			//	max # of bounces for ray (default 5)
			else if(!splitline[0].compare("maxdepth")){
				maxDepth = atoi(splitline[1].c_str());
			}
			//output filename
			//	output file to write image to 
			else if(!splitline[0].compare("output")){
				outputName = splitline[1];
			}

			//camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
			//	speciﬁes the camera in the standard way, as in homework 2.
			else if(!splitline[0].compare("camera")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				lookFrom = Vertex3f(x, y, z);
				x = atof(splitline[4].c_str());
				y = atof(splitline[5].c_str());
				z = atof(splitline[6].c_str());
				lookToward = Vertex3f(x, y, z);
				x = atof(splitline[7].c_str());
				y = atof(splitline[8].c_str());
				z = atof(splitline[9].c_str());
				up = Vector3f(x, y, z).Normalize();
				fov = atof(splitline[10].c_str());
			}

			//sphere x y z radius
			//	Deﬁnes a sphere with a given position and radius.
			else if(!splitline[0].compare("sphere")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				float radius = atof(splitline[4].c_str());
				Sphere* obj = new Sphere(x, y, z, radius, curTransform, curQuality);
				objects.push_back(obj);
			}
			//maxverts number
			//	Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
			//	It must be set before vertices are deﬁned.
			else if(!splitline[0].compare("maxverts")){
				/* IGNORE! */
			}
			//maxvertnorms number
			//	Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
			//	It must be set before vertices with normals are deﬁned.
			else if(!splitline[0].compare("maxvertnorms")){
				/* IGNORE! */
			}
			//vertex x y z
			//	Deﬁnes a vertex at the given location.
			//	The vertex is put into a pile, starting to be numbered at 0.
			else if(!splitline[0].compare("vertex")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				Vertex3f vertex(x, y, z);
				vertices.push_back(vertex);
			}
			//vertexnormal x y z nx ny nz
			//	Similar to the above, but deﬁne a surface normal with each vertex.
			//	The vertex and vertexnormal set of vertices are completely independent
			//	(as are maxverts and maxvertnorms).
			else if(!splitline[0].compare("vertexnormal")){
				VertexNormalPair pair;
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				pair.vertex = Vertex3f(x, y, z);
				float nx = atof(splitline[4].c_str());
				float ny = atof(splitline[5].c_str());
				float nz = atof(splitline[6].c_str());
				pair.normal = Vector3f(nx, ny, nz);
				vertexNormalPairs.push_back(pair);
			}
			//tri v1 v2 v3
			//	Create a triangle out of the vertices involved (which have previously been speciﬁed with
			//	the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
			//	should internally compute a face normal for this triangle.
			else if(!splitline[0].compare("tri")){
				int i0 = atof(splitline[1].c_str());
				int i1 = atof(splitline[2].c_str());
				int i2 = atof(splitline[3].c_str());
				Triangle* obj = new Triangle(vertices[i0], vertices[i1], vertices[i2], curTransform, curQuality);
				objects.push_back(obj);
			}
			//trinormal v1 v2 v3
			//	Same as above but for vertices speciﬁed with normals.
			//	In this case, each vertex has an associated normal, 
			//	and when doing shading, you should interpolate the normals 
			//	for intermediate points on the triangle.
			else if(!splitline[0].compare("trinormal")){
				int i0 = atof(splitline[1].c_str());
				int i1 = atof(splitline[2].c_str());
				int i2 = atof(splitline[3].c_str());
				VertexNormalPair vn0 = vertexNormalPairs[i0];
				VertexNormalPair vn1 = vertexNormalPairs[i1];
				VertexNormalPair vn2 = vertexNormalPairs[i2];
				Triangle* obj = new Triangle(vn0.vertex, vn1.vertex, vn2.vertex, vn0.normal, vn1.normal, vn2.normal, curTransform, curQuality);
				objects.push_back(obj);
			}

			//translate x y z
			//	A translation 3-vector
			else if(!splitline[0].compare("translate")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				curTransform = curTransform.translateFirst(x, y, z);
			}
			//rotate x y z angle
			//	Rotate by angle (in degrees) about the given axis as in OpenGL.
			else if(!splitline[0].compare("rotate")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				float angle = atof(splitline[4].c_str());
				curTransform = curTransform.rotateFirst(x, y, z, angle);
			}
			//scale x y z
			//	Scale by the corresponding amount in each axis (a non-uniform scaling).
			else if(!splitline[0].compare("scale")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				curTransform = curTransform.scaleFirst(x, y, z);
			}
			//pushTransform
			//	Push the current modeling transform on the stack as in OpenGL. 
			//	You might want to do pushTransform immediately after setting 
			//	 the camera to preserve the “identity” transformation.
			else if(!splitline[0].compare("pushTransform")){
				transformStack.push(curTransform);
			}
			//popTransform
			//	Pop the current transform from the stack as in OpenGL. 
			//	The sequence of popTransform and pushTransform can be used if 
			//	desired before every primitive to reset the transformation 
			//	(assuming the initial camera transformation is on the stack as 
			//	discussed above).
			else if(!splitline[0].compare("popTransform")){
				curTransform = transformStack.top();
				transformStack.pop();
			}

			//directional x y z r g b
			//	The direction to the light source, and the color, as in OpenGL.
			else if(!splitline[0].compare("directional")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				Vector3f direction(-x, -y, -z);
				direction = curTransform.Get() * direction;
				float r = atof(splitline[4].c_str());
				float g = atof(splitline[5].c_str());
				float b = atof(splitline[6].c_str());
				Color3f color(r, g, b);
				DirectionalLight* light = new DirectionalLight(direction, color, curAttenuation);
				lights.push_back(light);
			}
			//point x y z r g b
			//	The location of a point source and the color, as in OpenGL.
			else if(!splitline[0].compare("point")){
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				Vertex3f point(x, y, z);
				point = curTransform.Get() * point;
				float r = atof(splitline[4].c_str());
				float g = atof(splitline[5].c_str());
				float b = atof(splitline[6].c_str());
				Color3f color(r, g, b);
				PointLight* light = new PointLight(point, color, curAttenuation);
				lights.push_back(light);
			}
			//attenuation const linear quadratic
			//	Sets the constant, linear and quadratic attenuations 
			//	(default 1,0,0) as in OpenGL.
			else if(!splitline[0].compare("attenuation")){
				curAttenuation.constant  = atof(splitline[1].c_str());
				curAttenuation.linear    = atof(splitline[2].c_str());
				curAttenuation.quadratic = atof(splitline[3].c_str());
			}
			//ambient r g b
			//	The global ambient color to be added for each object 
			//	(default is .2,.2,.2)
			else if(!splitline[0].compare("ambient")){
				float r = atof(splitline[1].c_str());
				float g = atof(splitline[2].c_str());
				float b = atof(splitline[3].c_str());
				curQuality.ambient = Color3f(r, g, b);
			}

			//diﬀuse r g b
			//	speciﬁes the diﬀuse color of the surface.
			else if(!splitline[0].compare("diffuse")){
				float r = atof(splitline[1].c_str());
				float g = atof(splitline[2].c_str());
				float b = atof(splitline[3].c_str());
				curQuality.diffuse = Color3f(r, g, b);
			}
			//specular r g b 
			//	speciﬁes the specular color of the surface.
			else if(!splitline[0].compare("specular")){
				float r = atof(splitline[1].c_str());
				float g = atof(splitline[2].c_str());
				float b = atof(splitline[3].c_str());
				curQuality.specular = Color3f(r, g, b);
			}
			//shininess s
			//	speciﬁes the shininess of the surface.
			else if(!splitline[0].compare("shininess")){
				curQuality.shininess = atof(splitline[1].c_str());
			}
			//emission r g b
			//	gives the emissive color of the surface.
			else if(!splitline[0].compare("emission")){
				float r = atof(splitline[1].c_str());
				float g = atof(splitline[2].c_str());
				float b = atof(splitline[3].c_str());
				curQuality.emission = Color3f(r, g, b);
			} else {
				cerr<<"Unknown command: "<<splitline[0]<<endl;
			}
			//Update the progress.
			curTime = time(NULL);
			if(showProgress && difftime(curTime, lastUpdate) > progressWait){
				fileDone = in.tellg();
				double whole;
				modf(10000.0f*((float)fileDone)/((float)fileSize), &whole);
				cout<<" ... "<<(whole/100.0f)<<"%\n";
				cout.flush();
				lastUpdate = curTime;
			}
		}
	}
	cout<<"Reading finished successfully!\n";
}

Scene::~Scene(){
	std::list<Object*>::iterator obj;
	for(obj = objects.begin();obj != objects.end();obj++){
		delete *obj;
	}
	std::list<Light*>::iterator light;
	for(light = lights.begin();light != lights.end();light++){
		delete *light;
	}
}
