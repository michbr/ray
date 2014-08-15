#include "materialparser.h"
#include <iostream>
#include <sstream>

using namespace std;

static const string NEW_MATERIAL = "newmtl";
static const string AMBIENT = "Ka";
static const string DIFFUSE = "Kd";
static const string SPECULAR = "Ks";
static const string SHINY = "Ns";
static const string TRANSPARENT = "Tr";
static const string ALT_TRANSPARENT = "d";
static const string REFRACTION_INDEX = "Ni";
static const string ILLUMINATION_MODEL = "illum";


static const char ERR_STATE = -1;
static const char START_STATE = 0;
static const char ACTIVE_STATE = 1;
static const char NAMED_STATE = 2;
static const char AMBIENT_STATE = 3;
static const char DIFFUSE_STATE = 4;
static const char SPECULAR_STATE = 5;
static const char SHINY_STATE = 6;
static const char TRANSPARENT_STATE = 7;
static const char REFRACTION_STATE = 8;
static const char ILLUMINATION_STATE = 9;
static const char D2 = 10;
static const char D3 = 11;

MaterialParser::MaterialParser() : materials() {
	current = new vector<double>();
	counter = 0;
}

void MaterialParser::changeState(Token t) {
	switch (state) {
	case START_STATE:
		if (t.getToken().compare(NEW_MATERIAL) == 0) {
			state = ACTIVE_STATE;
		}
		else
			state = ERR_STATE;
		break;
	case ACTIVE_STATE:
		state = NAMED_STATE;
		inProcess = new Material(t.getToken());
		materials.push_back(inProcess);
		break;
	case NAMED_STATE:
		state = parseToken(t);
		break;
	case AMBIENT_STATE:
		initiatingState = state;
		current->push_back(getDouble(t));
		state = D2;
		break;
	case DIFFUSE_STATE:
		initiatingState = state;
		current->push_back(getDouble(t));
		state = D2;
		break;
	case SPECULAR_STATE:
		initiatingState = state;
		current->push_back(getDouble(t));
		state = D2;
		break;
	case SHINY_STATE:
		inProcess->setShininess(getDouble(t));
		state = NAMED_STATE;
		counter++;
		break;
	case TRANSPARENT_STATE:
		inProcess->setTransparency(getDouble(t));
		state = NAMED_STATE;
		counter++;
		break;
	case REFRACTION_STATE:
		cerr << "The index of refraction is not yet implemented." << endl;
		state = NAMED_STATE;
		break;
	case ILLUMINATION_STATE:
		cerr << "The illumination modes are not yet implemented." << endl;
		state = NAMED_STATE;
		break;
	case D2:
		state = D3;
		current->push_back(getDouble(t));
		break;
	case D3:
		current->push_back(getDouble(t));
		if (initiatingState == AMBIENT_STATE)
			inProcess->setAmbient(current);
		else if (initiatingState == DIFFUSE_STATE)
			inProcess->setDiffuse(current);
		else if (initiatingState == SPECULAR_STATE)
			inProcess->setSpecular(current);
		else {
			cerr << "Illegal initalizing state reading material file." << endl;
			exit(1);
		}
		current = new vector<double>();
		state = NAMED_STATE;
		counter++;
		break;
	default:
		cerr << "Illegal state reading material file. (" << state << ")" << endl;
		exit(1);
	}
}

double MaterialParser::getDouble(Token &t) {
	stringstream convert(t.getToken());
	double result;
	if (convert >> result)
		return result;
	else {
		cerr << "Corrupt or incorrect material file." << endl;
		exit(1);
	}	
}

char MaterialParser::parseToken(Token & t) {
	if (t.getToken().compare(AMBIENT) == 0)
		return AMBIENT_STATE;
	else if (t.getToken().compare(DIFFUSE) == 0)
		return DIFFUSE_STATE;
	else if (t.getToken().compare(SPECULAR) == 0)
		return SPECULAR_STATE;
	else if (t.getToken().compare(SHINY) == 0)
		return SHINY_STATE;
	else if (t.getToken().compare(TRANSPARENT) == 0 || t.getToken().compare(ALT_TRANSPARENT) == 0)
		return TRANSPARENT_STATE;
	else if (t.getToken().compare(REFRACTION_INDEX))
		return REFRACTION_STATE;
	else if (t.getToken().compare(ILLUMINATION_MODEL))
		return ILLUMINATION_STATE;
	else if (t.getToken().compare(NEW_MATERIAL))
		return ACTIVE_STATE;
	else return ERR_STATE;
}

vector<Material *> & MaterialParser::getMaterials() {
	return materials;
}

/*int main(int argc, char* argv[]) {
	MaterialParser test;
	test.tokenize("star.mtl");
	vector<Material *> mats = test.getMaterials();
	cout << "Done." << endl;
}*/