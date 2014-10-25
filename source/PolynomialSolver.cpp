// PolynomialSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Poly_Parser.h"
#include <thread>
#include <cmath>

int _tmain(int argc, _TCHAR* argv[])
{
	Poly_Parser poly_parser("x^4-2x^3+7x^2-16x+4");

	Polynomial poly(poly_parser.values, 100);

	poly.solve();

	return 0;
}

