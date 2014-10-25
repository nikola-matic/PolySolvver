#ifndef __POLY_PARSER__
#define __POLY_PARSER__

#include <string>
#include <iostream>
#include <vector>

struct poly_t {
	int multiplier;
	int exponent;

	poly_t(int multiplier__, int exponent__) :
		multiplier(multiplier__), exponent(exponent__) {}
};

class Poly_Parser {
private:
	//std::vector<poly_t> values;
	std::string current_mul;
	std::string current_exp;
	std::string expression;
	int index;

public:
	std::vector<poly_t> values;

	Poly_Parser(std::string expression__);

	bool terminus_next();
	bool is_alpha(char c);

	void step_one(char c);
	void step_two(char c);
	void step_three(char c);
	void step_four(char c);

	void finalize();
};

#endif