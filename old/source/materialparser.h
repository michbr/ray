#ifndef MATERIAL_PARSER_OBJ_H
#define MATERIAL_PARSER_OBJ_H

#include "parser.h"
#include "material.h"

class MaterialParser : public Parser {
private:
	//std::vector<Material> materials;
	char initiatingState = 0;
	char state = 0;
	virtual void changeState(Token t);
	char parseToken(Token & t);
	double getDouble(Token & t);
	std::vector<Material * > materials;
	Material * inProcess;
	int counter;
	std::vector<double> * current;
public:
	std::vector<Material *> & getMaterials();
	MaterialParser();
	//addEvent(Token t);
};

#endif