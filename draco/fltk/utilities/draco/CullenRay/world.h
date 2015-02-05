
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#ifndef RAY_WORLD_H
#define RAY_WORLD_H

#include "mesh.h"
#include "sphere.h"
#include "lightSource.h"
#include "camera.h"

#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <cfloat>
#include <ctime>


class World {
	public:
		
		//////////////////////
		// constant members //
		//////////////////////
		
		const double REFLECTION_DEPTH_PENALTY = 1;
		const double REFRACTION_DEPTH_PENALTY = 0;
		const clock_t PROGRESS_UPDATE_DELAY = 5 *CLOCKS_PER_SEC;
		
		
		///////////////////
		// dynamic members //
		///////////////////
		
		std::string sceneName;		// the name of the current scene.  Set when render() called
		unsigned short xRes, yRes;		// the x and y resolution of the current scene
		unsigned short recursion;		// the recursion depth for the current scene
		double ambientLight=20;			// the ambient light level in the scene, from 0 - 255
		std::list<Mesh> meshes;			// the list of meshes in the current scene
		std::list<Sphere> spheres;		// the list of spheres in the current scene
		std::vector<Material> materials;		// the list of materials used in the current scene
		std::map<std::string, unsigned short> materialMap;		// a map of material names to material indices
		std::list<Camera> cameras;		// the list of cameras for the current scene
		std::list<LightSource> lights;	// the list of lights for the current scene
		
		
		////////////////////
		// public methods //
		////////////////////
		
		// basic constructor initializes defaults
		World();
		
		// adds a .obj file to the world model
		void addObjects(char const *objectFilename);
		
		// renders the current world model with cameras, lights, and renders specified in the command file
		void render(char *commandFilename);
		
		// traces a ray through the current world model and returns the calculated color
		Color trace(const Ray3 &ray, double depth=0, double minDistance=0, double maxDistance=DBL_MAX, double *distance=NULL) const;
		
		// returns the distance along the ray before a collision with an object in the world model
		double intersection(const Ray3 &ray, double minDistance=0, double maxDistance=DBL_MAX) const;
		
		
	private:
		
		
		//////////////////////
		// internal methods //
		//////////////////////
		
		// reads a material file, adding to the material list and map
		void readMaterials(const std::string &fileName);
		
		// reads a line from the command file, adding whatever is specified to the world model
		void readCommand(const std::string &line);
		
		// calculates the lighting for the given ray collision
		Color calculateLight(const Ray3 &ray, const Collision &col) const;
};

#endif // RAY_WORLD_H