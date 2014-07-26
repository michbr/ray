#ifndef MATERIAL_OBJECT_H
#define MATERIAL_OBJECT_H

#include "light.h"

#include <fstream>
#include <vector>
#include <string>

class Material {
    private:
	std::vector<std::string> names;
	std::vector<std::vector<double> *> * Ka;
	std::vector<std::vector<double> *> * Kd;
	std::vector<std::vector<double> *> * Ks;
	std::vector<double> Ns;
	std::vector<double> Tr;
	void add_material(std::fstream &);
	std::vector<std::vector<double> *> * prepare_matrix(std::vector<double> *) const;
    public:
	Material();
	void load_materials(std::string);
	std::vector<int> * color_ambient(std::string, const std::vector<int> *) const;
	std::vector<int> * color_diffuse(std::string, const std::vector<int> *, double) const;
	std::vector<int> * color_specular(std::string, const std::vector<int> *, double) const;
	std::vector<int> * color_reflection(std::string, const std::vector<int> *) const;
	double get_tr (std::string) const;
};

#endif