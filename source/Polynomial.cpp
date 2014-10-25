#include "stdafx.h"

Polynomial::Polynomial(std::vector<poly_t> values__, int iteration_roof__) :
	values(values__), iteration_roof(iteration_roof__)
{

}

int Polynomial::sign(double num) {
	return (num < 0) ? -1 : 1;
}

bool Polynomial::in_range(double num, double centre, double deviation) {
	if((num <= centre + deviation) && (num >= centre - deviation)) return true;
	return false;
}

void Polynomial::range_positive() {
	for(double i = 0, incr = 0.1; i < iteration_roof; i += incr) {
		if(sign(poly_val(i)) != sign(poly_val(i+incr))) {
			std::cout << "root in range (" << i << "," << i+incr << ")\n";
			calc_root(i, i+incr);
		}
	}
}

void Polynomial::range_negative() {
	for(double incr = 0.1, i = 0 - incr; std::abs(i) < iteration_roof; i -= incr) {
		if(sign(poly_val(i)) != sign(poly_val(i-incr))) {
			std::cout << "root in range (" << i << "," << i-incr << ")\n";
			calc_root(i, i-incr);
		}
	}
}

void Polynomial::calc_root(double x1, double x2) {
	double direction = (x1 < x2) ? 1.0 : -1.0;
	for(double i = x1, incr = 0.0001; std::abs(i) <= std::abs(x2 + incr); i += (direction) * incr) {
		if(in_range(poly_val(i), 0, incr)) {
			roots.push_back(i);
			return;
		}
	}
}

double Polynomial::poly_val(double x) {
	double val = 0;

	for(auto it : values) {
		val += (it.multiplier * std::pow(x, it.exponent));
	}

	return val;
}

void Polynomial::solve() {
	std::cout << "\n#######################################################\n";
	std::cout << "##############         SOLVING ...      ###############\n";
	std::cout << "#######################################################\n";

	range_positive();
	range_negative();

	std::cout << "\n#######################################################\n";
	std::cout << "##############        SOLUTIONS        ################\n";
	std::cout << "#######################################################\n";

	for(auto it : roots) {
		std::cout << "root = " << it << "\n";
	}
}
