
/*
 * Cullen Eason
 * semimono
 * CS 410
 * Ross Beveridge
 */

#include "../world.h"
#include "dragonmath.h"
#include "../shape.h"
#include "../image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
#include <cfloat>
#include <cmath>

using namespace std;


///////////////////////
// utility functions //
///////////////////////

// strips a line from a file of comments and extraneous whitespace
void prepareLine(string &line) {
	size_t comment = line.find_first_of('#');
	if (comment != string::npos)
		line.erase(comment, line.size() -comment);
	line.erase(line.find_last_not_of(" \t\r\n")+1);
	line.erase(0, line.find_first_not_of(" \t\r\n"));
}

// calculates the direction of a refraction ray
Vector3<double> calcRefraction(const Vector3<double> &direction, const Vector3<double> &normal, double mu) {
	double dot = -direction.dot(normal);
	double radicand = sqrt(1 -mu *mu *(1 -dot *dot));
	if (radicand < 0)
		return Vector3<double>::zero;
	return ((mu * direction) + (mu * dot - radicand) * normal);
}


/////////////////
// World Model //
/////////////////

// contructor just initializes default material
World::World() {
	materialMap[string("default")];
}


// adds a .obj file's contents to the world model
/*void World::addObjects(char const *objectFilename) {
	
	// prepare the file and the meta data
	ifstream file(objectFilename);
	string line;
	unsigned short material = 0;
	meshes.push_back(Mesh());
	Mesh *mesh = &meshes.back();
	
	// iterate through the file
	while(!file.eof()) {
		
		// get a line and clean it
		getline(file, line);
		prepareLine(line);
		if (line.size() < 1) continue;
		istringstream lineStream(line);
		
		// get the parameter type and handle the line according to which type is found
		string type;
		lineStream >> type;
		
		// first check single character types
		if (type.size() == 1) {
			string name;
			Vector3<double> pos;
			double radius;
			Vector4<double> vec;
			switch(type[0]) {
				
				// the case for a sphere; reads a name, position, and radius
				case 's':
					lineStream >> name;
					lineStream >> pos;
					lineStream >> radius;
					spheres.push_back(Sphere(pos, radius, material));
					break;
				
				// the case for a vertex; reads only a position
				case 'v':
					lineStream >> vec;
					mesh->vertices.push_back(vec);
					break;
				
				// the case for a face; reads a list of vertex indices
				case 'f':
					if (mesh->groups.size() < 1)
						mesh->groups.push_back(TriangleGroup());
					unsigned short first, second, last;
					lineStream >> first;
					lineStream >> last;
					do {
						second = last;
						lineStream >> last;
						mesh->addTriangle(first -1, second -1, last -1, material);
					} while(!lineStream.eof() && !lineStream.fail());
					break;
				
				// the case for a group; ignores name and just creates division in current mesh object
				case 'g':
					mesh->groups.push_back(TriangleGroup());
					break;
				default:
					cerr << "ERROR: Unknown object parameter type in " << objectFilename << ": " << line << endl;
					exit(1);
			}
		
		// read the material library
		} else if (type == string("mtllib")) {
			string materialLib;
			lineStream >> materialLib;
			if (materialLib[0] != '/') {
				string path(objectFilename);
				size_t last = path.find_last_of('/');
				if (last != string::npos) {
					path = path.substr(0, last +1);
					materialLib = path +materialLib;
				}
			}
			readMaterials(materialLib);
		
		// change current material
		} else if (type == string("usemtl")) {
			string matName;
			lineStream >> matName;
			material = materialMap[matName];
		} else {
			cerr << "ERROR: Unknown object parameter type in " << objectFilename << ": " << line << endl;
			exit(1);
		}
		
		if (lineStream.fail()) {
			cerr << "ERROR: Improperly formatted specification in " << objectFilename << ": " << line << endl;
			exit(-1);
		}
	}
	mesh->calcVertNormals();
	file.close();
}*/

// renders the current world model with the specified command file
void World::render(char *commandFilename) {
	
	// read in the command file
	ifstream file(commandFilename);
	string line;
	cameras.clear();
	lights.clear();
	while(!file.eof()) {
		getline(file, line);
		prepareLine(line);
		if (line.size() < 1) continue;
		readCommand(line);
	}
	file.close();
	
	// iterate through the cameras and render each one
	for(Camera cam: cameras) {
		
		// calculate camera axis
		cout << "Rendering camera " << cam.name << endl;
		Vector3<double> zDir = cam.normal.normal();
		Vector3<double> xDir = cam.up.cross(zDir).normal();
		Vector3<double> yDir = zDir.cross(xDir);
		
		//++xRes;
		//++yRes;
		
		// calculate pre-comp values
		Vector2<double> viewPlaneSize(2.0 *((double)xRes /(double)yRes), 2);
		Vector2<double> viewPlaneOffset(-viewPlaneSize.x /2, -viewPlaneSize.y /2);
		Vector2<double> pixelMult(viewPlaneSize.x /(xRes -1), viewPlaneSize.y /(yRes -1));
		Image image(xRes, yRes);
		clock_t lastProgressUpdate = clock();
		
		// perform ray tracing and fill the image
		for(int y=0; y<yRes; ++y) {
			for(int x=0; x<xRes; ++x) {
				//Ray3<double> ray;
				//ray.position = cam.position;
				Vector2<double> gridPos(x *pixelMult.x +viewPlaneOffset.x, y *pixelMult.y +viewPlaneOffset.y);
				Vector3<double> pix = Vector3<double>(gridPos.x, gridPos.y, cam.near).normal();
				Vector3<double> rayDir = pix.x *xDir +pix.y *yDir -pix.z *zDir;
				Ray3<double> ray(cam.position, rayDir);
				
				double distance;
				image.set(x, y, trace(ray, recursion, cam.near /pix.z, cam.far /pix.z, &distance));
				image.set(x, y, distance);	// save off the distance for antialiasing
			}
			
			// output progress if enough time elapsed since last update
			if (clock() -lastProgressUpdate >= PROGRESS_UPDATE_DELAY) {
				lastProgressUpdate = clock();
				cout << "\t" << (y *100 /(double)yRes) << "% complete" << endl;
			}
		}
		
		//--xRes;
		//--yRes;
		image.antialias(0.1);
		
		// write image
		ofstream colorOut((sceneName +'_' +cam.name +".ppm").c_str());
		colorOut << "P3 " << xRes << " " << yRes << " 256" << endl;
		for(int y=yRes-1; y>=0; --y) {
			for(int x=0; x<xRes; ++x) {
				Color colorPixel = image.get(x, y);
				//Color colorPixel =
				//	image[x][y] *0.25 +
				//	image[x][y+1] *0.25 +
				//	image[x+1][y+1] *0.25 +
				//	image[x+1][y] *0.25;
				colorOut << colorPixel << " ";
			}
			colorOut << endl;
		}
		colorOut.close();
		cout << "\tcompleted" << endl;
	}
}

// traces a ray through the current world model, returning the color for that ray
Color World::trace(const Ray3<double> &ray, double depth, double minDistance, double maxDistance, double *distance) const {
	Collision col;
	
	// find closest collision with a sphere
	col.distance = maxDistance;
	for(list<Sphere>::const_iterator it=spheres.cbegin(); it != spheres.cend(); ++it) {
		Collision newCol = it->collision(ray);
		if (newCol.distance >= minDistance && newCol.distance <= col.distance) {
			col = newCol;
		}
	}
	// find closest collision with a polgyon
	for(list<Mesh>::const_iterator it=meshes.cbegin(); it != meshes.cend(); ++it) {
		Collision newCol = it->collision(ray);
		if (newCol.distance >= minDistance && newCol.distance <= col.distance) {
			col = newCol;
		}
	}
	
	Color colorPixel(0, 0, 0);
	
	// handle reflection and refraction
	Vector3<double> norm = (col.normal.dot(ray.direction) > 0)? -col.normal: col.normal;
	double extraDis = 0;
	if (norm != Vector3<double>::zero) {
		colorPixel = calculateLight(ray, col);
		
		const Material &mat = materials[col.material];
		
		// reflection
		double ref = mat.reflectance;
		if (depth > 1 && ref > 0) {

			Vector3<double> intermediate = -ray.direction.dot(norm) *norm;
			Vector3<double> newDir = intermediate *2.0 +ray.direction;
			Vector3<double> newPos = col.position +newDir *0.01;
			Ray3<double> newRay(newPos, newDir);
			double tempDis;
			colorPixel += ref *trace(newRay, depth -REFLECTION_DEPTH_PENALTY, 0, DBL_MAX, &tempDis);
			extraDis -= tempDis *ref;
		}
		
		// refraction
		double alpha = mat.alpha;
		if (depth > 1 && alpha < 1) {
			const Sphere *sphere = dynamic_cast<const Sphere *>(col.shape);
			Color newCol;
			double tempDis;
			// refract through a sphere
			if (sphere == NULL) {
				double index = (col.normal == norm)? 1 /mat.refractionIndex: mat.refractionIndex;
				Vector3<double> T = calcRefraction(ray.direction, norm, index);
				if (T.magnitudeSquared() != 0) {
					Ray3<double> newRay(col.position, T);
					newRay.position += T *0.01;
					newCol = trace(newRay, depth -REFRACTION_DEPTH_PENALTY, 0, DBL_MAX, &tempDis);
				}
			// refract through a polygon (only works properly if the bakcside culling is disabled)
			} else {
				Vector3<double> T = calcRefraction(ray.direction, norm, 1 /mat.refractionIndex);
				if (T.magnitudeSquared() != 0) {

					Vector3<double> newPos = col.position +(sphere->position -col.position).dot(T) *T *2.0;
					Vector3<double> newDir = calcRefraction(T, (sphere->position - newPos) /sphere->radius, mat.refractionIndex);
					Ray3<double> newRay(newPos, newDir);
					newCol = trace(newRay, depth -REFRACTION_DEPTH_PENALTY, 0, DBL_MAX, &tempDis);
				}
			}
			extraDis = (1 -alpha) *tempDis +alpha *extraDis;
			colorPixel = (1 -alpha) *newCol +alpha *colorPixel *mat.refractionAtt;
		}
	}
	
	if (distance != NULL)
		*distance = col.distance +extraDis;
	return colorPixel;
}

// calculates the lighting for the given ray collision
Color World::calculateLight(const Ray3<double> &ray, const Collision &col) const {
	Color colorPixel(0, 0, 0);
	Material mat = materials[col.material];
	Vector3<double> norm = (col.normal.dot(ray.direction) > 0)? -col.normal: col.normal;
	for(list<LightSource>::const_iterator it=lights.cbegin(); it!=lights.cend(); ++it) {
		
		// calculate direction
		Vector3<double> toLight(0,0,0);
		if (col.position.w == 0) {
			toLight = (it->position -col.position); // TODO: handle this a little better
		} else {
			toLight = (it->position -col.position *it->position.w /col.position.w);
		}
		
		if (toLight.dot(norm) < 0)
			continue;
		
		// check for shadow
		double distance = toLight.magnitude();
		Vector3<double> lightDir = toLight /distance;
		if (intersection(Ray3<double>(col.position +toLight, -lightDir), 0, distance -0.001) < distance -0.001)
			continue;
		
		// add diffuse reflection
		colorPixel += it->color *(mat.difCol *lightDir.dot(norm));
		
		// add specular reflection
		Vector3<double> intermediate = lightDir.dot(norm) *norm;
		Vector3<double> bounceDir = (intermediate -lightDir) *2.0 +lightDir;
		double cosign = -bounceDir.dot(ray.direction);
		if (cosign < 0)
			continue;
		cosign = pow(cosign, mat.specularity);
		if (cosign < 0.01)
			continue;
		colorPixel += mat.specCol *it->color *cosign;
	}
	colorPixel += mat.ambCol *(ambientLight /255.0);
	return colorPixel;
}

// returns the distance along the ray before a collision with an object in the world model
double World::intersection(const Ray3<double> &ray, double minDistance, double maxDistance) const {
	double dis = maxDistance;
	for(list<Sphere>::const_iterator it=spheres.cbegin(); it!=spheres.cend(); ++it) {
		double newDis = it->intersection(ray);
		if (newDis > minDistance && newDis < dis) {
			dis = newDis;
		}
	}
	for(list<Mesh>::const_iterator it=meshes.cbegin(); it != meshes.cend(); ++it) {
		double newDis = it->collision(ray).distance;
		if (newDis > minDistance && newDis < dis) {
			dis = newDis;
		}
	}
	return dis;
}

// reads a material file, adding to the material list and map
void World::readMaterials(const string &fileName) {
	ifstream file(fileName);
	string curMatName;
	unsigned short curMat = 0;
	while(!file.eof()) {
		
		// get and clean the line
		string line;
		getline(file, line);
		prepareLine(line);
		if (line.size() < 1) continue;
		
		// get the element type
		istringstream lineStream(line);
		string type;
		lineStream >> type;
		for(size_t i=0; i<type.size(); ++i)
			type[i] = tolower(type[i]);
		
		// check for beginning new material specficiation
		if (type == string("newmtl")) {
			lineStream >> curMatName;
			map<string, unsigned short>::iterator it = materialMap.find(curMatName);
			if (it == materialMap.end()) {
				curMat = materials.size();
				materials.resize(materials.size() +1);
				materialMap[curMatName] = curMat;
			} else {
				curMat = it->second;
			}
		} else if (curMatName.size() < 1) {
			cerr << "ERROR: Material specification in " << fileName << " failed to call 'newmtl'" << endl;
			exit(-1);
			
		// handle ambient color specification
		} else if (type == string("ka")) {
			double val;
			lineStream >> val;
			materials[curMat].ambCol.r = val;
			lineStream >> val;
			materials[curMat].ambCol.g = val;
			lineStream >> val;
			materials[curMat].ambCol.b = val;
			
		// handle diffuse color specification
		} else if (type == string("kd")) {
			double val;
			lineStream >> val;
			materials[curMat].difCol.r = val;
			lineStream >> val;
			materials[curMat].difCol.g = val;
			lineStream >> val;
			materials[curMat].difCol.b = val;
			
		// handle specular color specification
		} else if (type == string("ks")) {
			double val;
			lineStream >> val;
			materials[curMat].specCol.r = val;
			lineStream >> val;
			materials[curMat].specCol.g = val;
			lineStream >> val;
			materials[curMat].specCol.b = val;
			
		// handle specularity specification
		} else if (type == string("ns")) {
			double val;
			lineStream >> val;
			materials[curMat].specularity = val;
			
		// handle refraction index specification
		} else if (type == string("n1")) {
			double val;
			lineStream >> val;
			materials[curMat].refractionIndex = val;
			
		// handle transparency specification
		} else if (type == string("tr")) {
			double val;
			lineStream >> val;
			materials[curMat].alpha = val;
			
		// handle reflection specification
		} else if (type == string("kr")) {
			double val;
			lineStream >> val;
			materials[curMat].reflectance = val;
			
		// handle refraction attenuation specification
		} else if (type == string("krf")) {
			double val;
			lineStream >> val;
			materials[curMat].refractionAtt = val;
			
		// handle unknown specification
		} else {
			cerr << "Unknown material value type: " << type << endl;
			exit(1);
		}
		if (lineStream.fail() || lineStream.bad()) {
			cerr << "ERROR: Improperly formatted material specification in " << fileName << ": " << line << endl;
			exit(-1);
		}
	}
	file.close();
}

// reads a cleaned line from the command file, adding whatever is specified to the world model
/*void World::readCommand(const string &line) {
	
	// read the specification type
	istringstream stream(line);
	char type = 0;
	stream >> type;
	if (!stream.good()) return;
	string name;
	Vector3<double> pos, norm, up;
	double near, far;
	unsigned short width, height, rec;
	LightSource light;
	
	// handle the specific specification type
	switch(type) {
		// the case for a camera: reads the name, position, normal, up vector, near plane, and far plane
		case 'c':
			stream >> name;
			stream >> pos;
			stream >> norm;
			stream >> up;
			stream >> near; stream >> far;
			if (stream.fail() || stream.bad()) {
				cerr << "ERROR: Improperly formatted camera: " << line << endl;
				return;
			}
			cameras.push_back(Camera(name, pos, norm, up, near, far));
			break;
		
		// the case for a light; reads position and color
		case 'l':
			stream >> light;
			if (stream.fail() || stream.bad()) {
				cerr << "ERROR: Improperly formatted light source: " << line << endl;
				return;
			}
			lights.push_back(light);
			break;
		
		// the case for the render line; reads name, resolution, and recursion depth
		case 'r':
			stream >> name;
			stream >> width; stream >> height;
			stream >> rec;
			if (stream.fail() || stream.bad()) {
				cerr << "ERROR: Improperly formatted rendering: " << line << endl;
				return;
			}
			sceneName = name;
			xRes = width;
			yRes = height;
			recursion = rec;
			break;
		default:
			break;
	}
}*/


