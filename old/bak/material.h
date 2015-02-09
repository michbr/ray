#ifndef MATERIAL_OBJECT_H
#define MATERIAL_OBJECT_H

#include "texture.h"

#include <fstream>
#include <vector>
#include <string>

class Material {
private:
	std::string name;
	std::vector<double> * Ka;
	std::vector<double> * Kd;
	std::vector<double> * Ks;
	double Ns;
	double Tr;
	//void add_material(std::fstream &);
	std::vector<Texture *> textures;
	std::vector<std::vector<double> *> * prepare_matrix(std::vector<double> *) const;
public:
	Material(std::string n);
	//void load_materials(std::string);

	void addTexture(std::string texPath);
	bool hasTexture() const;

	void setAmbient(std::vector<double> * a);
	void setDiffuse(std::vector<double> * a);
	void setSpecular(std::vector<double> * a);
	void setShininess(double a);
	void setTransparency(double a);

	std::vector<int> * color_ambient(const std::vector<int> *) const;
	std::vector<int> * color_diffuse(const std::vector<int> *, double) const;
	std::vector<int> * color_diffuse(const std::vector<int> *, double, double, double) const;
	std::vector<int> * color_specular(const std::vector<int> *, double) const;
	std::vector<int> * color_reflection(const std::vector<int> *) const;

	std::string getName();
	
	double get_tr () const;
};

#endif
