#ifndef MATHS_H
#define MATHS_H

namespace Maths {
	float degToRad(float degreeP) {
		return degreeP * PI / 180.0f;
	}

	float radToDeg(float radP) {
		return radP * 180.0f / PI;
	}

	bool isOdd(int numP) {
		return numP % 2 == 0;
	}

	typedef struct Vector2Int {
		int x;
		int y;
	} Vector2Int;
}

#endif // MATHS_H
