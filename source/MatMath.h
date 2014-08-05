#ifndef MATMATH_H
#define MATMATH_H

#include <vector>

//Vectors
std::vector<double> * normalize(const std::vector<double> *);
std::vector<double> * cross_product(const std::vector<double> *, const std::vector<double> *);
double dot_product(const std::vector<double> *, const std::vector<double> *);
std::vector<double>* make_perpendicular(const std::vector<double> *);
double magnitude(const std::vector<double> *);
std::vector<double> * add(const std::vector<double> *, const std::vector<double> *);
std::vector<double> * subtract(const std::vector<double> *, const std::vector<double> *);
std::vector<double> * scale(const std::vector<double> *, double);
bool is_equal(const std::vector<double> * a, const std::vector<double> * b);

//Matrices
std::vector<std::vector<double>*> * multiply(const std::vector<std::vector<double> *> *, const std::vector<std::vector<double> *> * );






#endif
