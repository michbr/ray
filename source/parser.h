#ifndef ABSTRACT_PARSER_OBJ
#define ABSTRACT_PARSER_OBJ

#include <string>
#include <queue>

class Parser {
protected:
	class Token {
	private:
		std::string data;
	public:
		Token(std::string line_in);
		std::string getToken();
	};
	std::queue<Token> tokens;
	virtual void changeState(Token t) = 0;
public:
	Parser();
	void tokenize(std::string filename);
};

#endif