#include "BernsteinBasisPolynomial.h"
#include <cmath>

using namespace std;

// constructor for b(v,n) with defaults
BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) : fFactor(Combination(aV,aN)) {}

// call operator to calculate Berstein base
// polynomial for a given x (i.e., aX)
double BernsteinBasisPolynomial::operator()(double aX) const {
	double one = fFactor();
	double second = pow(aX, fFactor.getK());
	double nMinusV = fFactor.getN() - fFactor.getK();
	double third = pow(1 - aX, nMinusV);

	return one * second * third;
}