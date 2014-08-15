#include "parser.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Parser::Token::Token(string line_in) {
	data = line_in;
}

string Parser::Token::getToken() {
	return data;
}

Parser::Parser() : tokens() {

}

string stripComments(string line) {
	if (line.empty()) return "";
	if (line.at(0) == '#') return "";
	size_t pos;
	if (pos = line.find("#") != string::npos)
		return line.substr(pos);
	return line;
}

void Parser::tokenize(string filename)  {
	string line;
	fstream input;
	input.open(filename.c_str());
	while (std::getline(input, line)) {
		size_t pos = 0;
		line = stripComments(line);
		while ((pos = line.find(" ")) != std::string::npos && !line.empty()) {
			//tokens.push(*(new Token(line.substr(0, pos))));
			changeState(*(new Token(line.substr(0, pos))));
			line.erase(0, pos + 1);
		}
		if (!line.empty())
			changeState(*(new Token(line)));
	}
}