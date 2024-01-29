#pragma once

#include "Polygon.h"

#include <stdexcept>

using namespace std;

Polygon::Polygon() : fNumberOfVertices(0) {

}

size_t Polygon::getNumberOfVertices() const{
	return fNumberOfVertices;
}
const Vector2D& Polygon::getVertex(size_t aIndex) const{
	if (aIndex < fNumberOfVertices) {
		return fVertices[aIndex];
	}
	throw out_of_range("Illegal index value.");
}

void Polygon::readData(std::istream& aIStream) {
	while (aIStream >> fVertices[fNumberOfVertices]) {
		fNumberOfVertices++;
	}
}

float Polygon::getPerimeter() const {
	float Result = 0.0;
	if (fNumberOfVertices > 2) {
		for (size_t i = 1; i < fNumberOfVertices; i++) {
			Result += (fVertices[i] - fVertices[i - 1]).length();
		}
		Result += (fVertices[0] + fVertices[fNumberOfVertices - 1]).length();
	}
	return Result;
}

Polygon Polygon::scale(float aScalar) const {
	Polygon res = *this;
	for (size_t i = 0; i < fNumberOfVertices; i++) {
		res.fVertices[i] = fVertices[i] * aScalar;
	}
	return res;
}

// Problem Set 1 extension
float Polygon::getSignedArea() const {
	float res = 0.0;
	if (fNumberOfVertices > 2) {
		for (size_t i = 0; i < fNumberOfVertices - 1; i++) {
			res += (fVertices[i].getX() * fVertices[i + 1].getY() -
				fVertices[i].getY() * fVertices[i + 1].getX());
		}
	}
	res += (fVertices[0].getX() * fVertices[fNumberOfVertices - 1].getY() -
		fVertices[0].getY() * fVertices[fNumberOfVertices - 1].getX());
	return  res;
}