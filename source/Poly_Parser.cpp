#include "stdafx.h"

Poly_Parser::Poly_Parser(std::string expression__) : 
	expression(expression__), current_mul(), index(0)
{
	if(expression.size()) {
		std::cout << "#######################################################\n";
		std::cout << "##############         PARSING ...      ###############\n";
		std::cout << "#######################################################\n";

		step_one(expression[0]);
	} else {
		std::cout << "warning: null string passed to Poly_Parser instance!\n";
	}
}

bool Poly_Parser::terminus_next() {
	if((index + 1) == expression.size()) return true;
	return false;
}

bool Poly_Parser::is_alpha(char c) {
	if(c >= 48 && c <= 57) return true;
	return false;
}

void Poly_Parser::finalize() {
	if(!current_exp.size()) current_exp += '0';
	std::cout << "extracting... mul = " << current_mul << " , exp = " << current_exp << "\n";

	int c_mul = 0, c_exp = 0;

	if(current_mul.size())  {
		c_mul = std::stoi(current_mul);
	}
	if(current_exp.size()) {
		c_exp = std::stoi(current_exp);
	}
	if(c_mul != 0) {
		values.push_back(poly_t(c_mul, c_exp));
	}

	current_mul.clear();
	current_exp.clear();
}

void Poly_Parser::step_one(char c) {
	if(current_mul.size()) {
		finalize();
	}

	std::cout << "parsing : " << c << "\n";

	switch(c) {
	case '-': 
		current_mul += c;
		if(!terminus_next()) step_three(expression[++index]);
		else finalize();
		break;
	case 'x':
		current_mul += '1';
		if(!terminus_next()) step_two(expression[++index]);
		else finalize();
		break;
	default:
		if(is_alpha(c)) {
			current_mul += c;
			if(!terminus_next()) step_three(expression[++index]);
			else finalize();
		} else {
			std::cout << "error: invalid character '" << c << "' in step one\n";
			return;
		}
	}
}

void Poly_Parser::step_two(char c) {

	std::cout << "parsing : " << c << "\n";

	switch(c) {
	case '+':
		current_exp += '1';
		finalize();
		if(!terminus_next()) step_three(expression[++index]);
		break;
	case '-':
		current_exp += '1';
		finalize();
		current_mul += c;
		if(!terminus_next()) step_three(expression[++index]);
		else finalize();
		break;
	case '^':
		if(!terminus_next()) step_four(expression[++index]);
		else {
			std::cout << "error: no alpha after '^'\n";
			return;
		}
		break;
	default:
		std::cout << "error: invalid character '" << c << "' in step two\n";
		return;
	}

}

void Poly_Parser::step_three(char c) {

	std::cout << "parsing : " << c << "\n";

	switch(c) {
	case '+':
		finalize();
		if(!terminus_next()) step_three(expression[++index]);
		break;
	case '-':
		finalize();
		current_mul += c;
		if(!terminus_next()) step_three(expression[++index]);
		else finalize();
		break;
	case 'x':
		if(expression[index-1] == '-' || expression[index-1] == '+') current_mul += '1';
		if(!terminus_next()) step_two(expression[++index]);
		else finalize();
		break;
	default:
		if(is_alpha(c)) {
			current_mul += c;
			if(!terminus_next()) step_three(expression[++index]);
			else finalize();
		} else {
			std::cout << "error: invalid character '" << c << "' in step three\n";
			return;
		}
	}
}

void Poly_Parser::step_four(char c) {

	std::cout << "parsing : " << c << "\n";

	switch(c) {
	case '+':
		finalize();
		if(!terminus_next()) step_three(expression[++index]);
		break;
	case '-':
		finalize();
		current_mul += c;
		if(!terminus_next()) step_three(expression[++index]);
		else finalize();
		break;
	default:
		if(is_alpha(c)) {
			current_exp += c;
			if(!terminus_next()) step_four(expression[++index]);
			else finalize();
		} else {
			std::cout << "error: invalid character '" << c << "' in step four\n";
			return;
		}
	}
}