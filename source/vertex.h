#ifndef VERTEX_OBJECT_H
#define VERTEX_OBJECT_H

#include <string>
#include <ostream>
#include <vector>

class Vertex {

private:
double x,y,z,w;

public:
Vertex(double, double, double, double);
Vertex(std::string);

void fix();

void rotate(double, double, double, double);
void arbitrary(std::vector<std::vector<double> *> *);
void translate(double, double, double);
void scale(double, double, double);

double get_x() const;
double get_y() const;
double get_z() const;
double get_w() const;

void set_w(double);

friend std::ostream & operator<<(std::ostream &, const Vertex &);
std::ostream & operator<<(std::ostream &);
};

std::ostream & operator<<(std::ostream &, const Vertex &);

#endif