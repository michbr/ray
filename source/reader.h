#ifndef READER_OBJECT_H
#define READER_OBJECT_H

#include "group.h"
#include "face.h"
#include "vertex.h"

#include "light.h"
#include "material.h"
#include "camera.h"
#include "face.h"

#include "renderer.h"

#include <vector>
#include <unordered_map>

class Reader {
	private:
		std::unordered_map<std::string, Material *> matMap;
		std::vector<int> used_vertices;
		std::vector<Vertex *> vertices;
		std::vector<Face *> faces;
		std::vector<Elipse *> elipses;
		std::vector<Group *> groups;
		std::vector<Camera *> cameras;
		std::vector<Light *> lights;
		std::vector<std::string> files;
		
		
		Group * current_group;
		Renderer * renderer;
		std::string current_material;
		Material * material;
		void tokenize(std::string);
	public:
		Reader();
		void read(std::string);
		void write(std::string);
		void wireframe(std::string);
		void raycast();
};

#endif
