// COS30008, Tutorial 3, 2022

#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial() :
    fDegree(0)
{
	for ( size_t i = 0; i <= MAX_DEGREE; i++ )
	{
		fCoeffs[i] = 0.0;
	}
}

bool Polynomial::operator==( const Polynomial& aRHS ) const
{
    bool Result = fDegree == aRHS.fDegree;
    
    for ( size_t i = 0; Result && i <= fDegree; i++ )
    {
        if ( fCoeffs[i] != aRHS.fCoeffs[i] )
        {
            Result = false;
        }
    }
    
    return Result;
}

Polynomial Polynomial::operator*( const Polynomial& aRight ) const
{
    // C = A * B
    
	Polynomial Result;
    
    Result.fDegree = fDegree + aRight.fDegree;
    
    for ( size_t i = 0; i <= fDegree; i++ )
    {
        for ( size_t j = 0; j <= aRight.fDegree; j++ )
        {
            Result.fCoeffs[i+j] += fCoeffs[i] * aRight.fCoeffs[j];
        }
    }
    
	return Result;
}

ostream& operator<<( ostream& aOStream, const Polynomial& aObject )
{
    bool lMustPrintPlus = false;
    
    for ( int i = static_cast<int>(aObject.fDegree); i >= 0; i-- )
    {
        if ( aObject.fCoeffs[i] != 0.0 )
        {
            if ( lMustPrintPlus )
            {
                aOStream << " + ";
            }
            else
            {
                lMustPrintPlus = true;
            }
            
            aOStream << aObject.fCoeffs[i] << "x^" << i;
        }
    }
    
    return aOStream;
}
                
istream& operator>>( istream& aIStream, Polynomial& aObject )
{
	// read degree
    size_t lDegree;
	
    aIStream >> lDegree;

    aObject.fDegree = lDegree <= MAX_POLYNOMIAL ? lDegree : MAX_POLYNOMIAL;

	// read coefficients (assume sound input)
    for ( int i = static_cast<int>(aObject.fDegree); i >= 0; i-- )
	{
		aIStream >> aObject.fCoeffs[i];
	}

	return aIStream;
}

// call operator to calculate polynomial for a given x (i.e., aX)
double Polynomial::operator()(double aX) const {
    double Result = 0.0;
    for (int i = 0; i <= fDegree; i++) {
        Result += fCoeffs[i] * pow(aX, i);
    }
    return Result;
}

// compute derivative: the derivative is a fresh polynomial with degree
// fDegree-1, the method does not change the current object
Polynomial Polynomial::getDerivative() const {
    Polynomial Result;

    Result.fDegree = fDegree - 1;

    for (int i = 1; fDegree != 0 && i <= fDegree; i++) {
        Result.fCoeffs[i - 1] = fCoeffs[i] * i;
    }
  
    return Result;
}

// compute indefinite integral: the indefinite integral is a fresh
// polynomial with degree fDegree+1
// the method does not change the current object
Polynomial Polynomial::getIndefiniteIntegral() const {
    Polynomial Result;

    Result.fDegree = fDegree + 1;

    for (int i = 1; i <= fDegree + 1; i++) {
        Result.fCoeffs[i] = fCoeffs[i - 1] / i;
    }
    return Result;
}

// calculate definite integral: the method does not change the current
// object; the method computes the indefinite integral and then
// calculates it for xlow and xhigh and returns the difference
double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const {
    Polynomial res = getIndefiniteIntegral();
    return res(aXHigh) - res(aXLow);
}
