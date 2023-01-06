#include <raymath.h>
#include "MathsUtils.h"

float MathsUtils::degToRad(float degreeP) {
	return degreeP * PI / 180.0f;
}

float MathsUtils::radToDeg(float radP) {
	return radP * 180.0f / PI;
}

bool MathsUtils::isOdd(int numP) {
	return numP % 2 == 0;
}