#include "Combination.h"


using namespace std;

Combination::Combination(size_t aN = 0, size_t aK = 0) : fN(aN), fK(aK) {}

size_t Combination::getN() const {
	return fN;
}
size_t Combination::getK() const {
	return fK;
}

unsigned long long Combination::operator()() const {
	unsigned long long res = 1;
	long long start = 0;

	for (long long i = 1; i <= fK; i++) {
		res *= (fN - start) / static_cast<double>(i);
		start++;
	}
	return res;
}