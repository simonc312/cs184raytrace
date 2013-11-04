#ifndef SCENE_HPP
#define SCENE_HPP

#include "Vector3f.hpp"
#include "Vertex3f.hpp"
#include "Ray.hpp"
#include "Objects.hpp"
#include "Lights.hpp"

#include <string>
#include <vector>
#include <list>

class Scene{
public:
	Scene(std::string file, int progressWait = -1);
	~Scene();

	int imgWidth;
	int imgHeight;
	std::string outputName;
	int maxDepth;
	Vertex3f lookFrom, lookToward;
	Vector3f up;//Noramlized.
	float fov;//Degrees!

	std::vector<Vertex3f> vertices;
	struct VertexNormalPair{
		Vertex3f vertex;
		Vector3f normal;
	};
	std::vector<VertexNormalPair> vertexNormalPairs;
	std::list<Object*> objects;

	std::list<Light*> lights;
private:
};

#endif//SCENE_HPP
