#ifndef __POLYNOMIAL__
#define __POLYNOMIAL__

#include "stdafx.h"

class Polynomial {
private:
	std::vector<poly_t> values;
	int unsigned iteration_roof;

private:
	void range_positive();
	void range_negative();
	void calc_root(double x1, double x2);
	int sign(double num);
	bool in_range(double num, double centre, double deviation);

public:
	std::vector<double> roots;
public:
	Polynomial(std::vector<poly_t> values__, int iteration_roof__);
	double poly_val(double x);
	void solve();
};

#endif